#include <rte_cycles.h>
#include <rte_eal.h>
#include <rte_ethdev.h>
#include <rte_ether.h>
#include <rte_ip.h>
#include <rte_lcore.h>
#include <rte_malloc.h>
#include <rte_mbuf.h>
#include <rte_random.h>
#include <rte_udp.h>
#include <signal.h>
#include <stdint.h>
#include <time.h>

#include <chrono>
#include <iomanip>
#include <iostream>
#include <thread>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "pktgen.h"
#include "tsc_clock.h"

// Source/destination MACs
struct rte_ether_addr src_mac = {{0xb4, 0x96, 0x91, 0xa4, 0x02, 0xe9}};
struct rte_ether_addr dst_mac = {{0xb4, 0x96, 0x91, 0xa4, 0x04, 0x21}};

volatile bool quit;
struct config_t config;

static void signal_handler(int signum) {
  (void)signum;
  quit = true;
}

static const struct rte_eth_conf port_conf_default = {};

// Per worker configuration
struct worker_config_t {
  struct rte_mempool* pool;
  uint16_t queue_id;

  bytes_t pkt_size;
  std::vector<flow_t> flows;

  const runtime_config_t* runtime;

  worker_config_t(struct rte_mempool* _pool, uint16_t _queue_id,
                  bytes_t _pkt_size, const std::vector<flow_t>& _flows,
                  const runtime_config_t* _runtime)
      : pool(_pool),
        queue_id(_queue_id),
        pkt_size(_pkt_size),
        flows(_flows),
        runtime(_runtime) {}
};

// Gets number of mbufs per worker.
//
// Each worker will be responsible for its own flows. The sum of all the flows
// from all the workers equals the requested total number of flows.
// Due to churn, each flow has a corresponding and unique churn flow. The worker
// will continuously alternate between each flow and its corresponding churn
// flow.
//
// This alternation is not simultaneous for all flows. To smooth out the
// transitions, we iteratively transition one flow at a time. This means we
// require a list of mbufs for each array of flows.
//
// Take F as the number of worker flows. A flow state array contains all the
// flows to be transmited, thus having F/2 length. In total, we will have (F/2)
// + 1 of these arrays, each transitioning one more flow than the previous one,
// with the last one containing only churn flows. In total, we have F unique
// flows, but (F/2)+1 arrays.
//
// Concluding, because we have (F/2)+1 with each array containing F/2 flows, we
// require in total (F/2) * ((F/2)+1) mbufs, or (F**2 + 2F)/4.
//
// Finally, the total number of mbufs must be a power of 2, so we must find the
// lowest power of 2 bigger than what we require.
//
// Example:
// Total flows = 8
// Flows = { f0, f1, f2, f3, f0', f1', f2', f3' }
// Arrays = [
//   [ f0, f1, f2, f3 ]
//   [ f0', f1, f2, f3 ]
//   [ f0', f1', f2, f3 ]
//   [ f0', f1', f2', f3 ]
//   [ f0', f1', f2', f3' ]
// ]
// Total number of arrays = F/2 + 1 = 5
// Total number of mbufs = (F**2 + 2F)/4 = 20

void pktgen_stats_display(uint16_t port_id) {
  struct rte_eth_stats stats;

  constexpr uint16_t max_num_stats = 1024;

  rte_eth_stats_get(port_id, &stats);

  printf("\n==== Statistics ====\n");
  printf("Port %" PRIu8 "\n", port_id);
  printf("    ipackets: %" PRIu64 "\n", stats.ipackets);
  printf("    opackets: %" PRIu64 "\n", stats.opackets);
  printf("    ibytes: %" PRIu64 "\n", stats.ibytes);
  printf("    obytes: %" PRIu64 "\n", stats.obytes);
  printf("    imissed: %" PRIu64 "\n", stats.imissed);
  printf("    oerrors: %" PRIu64 "\n", stats.oerrors);
  printf("    rx_nombuf: %" PRIu64 "\n", stats.rx_nombuf);
  printf("\n");

  printf("\n==== Extended Statistics ====\n");
  int num_xstats = rte_eth_xstats_get(port_id, NULL, 0);
  struct rte_eth_xstat xstats[max_num_stats];
  if (rte_eth_xstats_get(port_id, xstats, num_xstats) != num_xstats) {
    printf("Cannot get xstats\n");
  }
  struct rte_eth_xstat_name xstats_names[max_num_stats];
  if (rte_eth_xstats_get_names(port_id, xstats_names, num_xstats) !=
      num_xstats) {
    printf("Cannot get xstats\n");
  }
  for (int i = 0; i < num_xstats; ++i) {
    printf("%s: %" PRIu64 "\n", xstats_names[i].name, xstats[i].value);
  }
  printf("\n");
}

// Initializes a given port using global settings.
static inline int port_init(uint16_t port, unsigned num_rx_queues,
                            unsigned num_tx_queues,
                            struct rte_mempool** mbuf_pools) {
  struct rte_eth_conf port_conf = port_conf_default;
  const uint16_t rx_rings = num_rx_queues, tx_rings = num_tx_queues;
  uint16_t nb_rxd = DESC_RING_SIZE;
  uint16_t nb_txd = DESC_RING_SIZE;
  int retval;
  uint16_t q;
  struct rte_eth_dev_info dev_info;
  struct rte_eth_txconf txconf;

  if (!rte_eth_dev_is_valid_port(port)) return -1;

  retval = rte_eth_dev_info_get(port, &dev_info);
  if (retval != 0) {
    printf("Error during getting device (port %u) info: %s\n", port,
           strerror(-retval));
    return retval;
  }

  if (dev_info.tx_offload_capa & RTE_ETH_TX_OFFLOAD_MBUF_FAST_FREE)
    port_conf.txmode.offloads |= RTE_ETH_TX_OFFLOAD_MBUF_FAST_FREE;

  if (dev_info.tx_offload_capa & RTE_ETH_TX_OFFLOAD_OUTER_IPV4_CKSUM)
    port_conf.txmode.offloads |= RTE_ETH_TX_OFFLOAD_OUTER_IPV4_CKSUM;

  if (dev_info.tx_offload_capa & RTE_ETH_TX_OFFLOAD_OUTER_UDP_CKSUM)
    port_conf.txmode.offloads |= RTE_ETH_TX_OFFLOAD_OUTER_UDP_CKSUM;

  // Enable RX in promiscuous mode, just in case
  rte_eth_promiscuous_enable(port);
  if (rte_eth_promiscuous_get(port) != 1) {
    return retval;
  }

  /* Configure the Ethernet device. */
  retval = rte_eth_dev_configure(port, rx_rings, tx_rings, &port_conf);
  if (retval != 0) return retval;

  retval = rte_eth_dev_adjust_nb_rx_tx_desc(port, &nb_rxd, &nb_txd);
  if (retval != 0) return retval;

  /* Allocate and set up 1 RX queue per RX worker port. */
  for (q = 0; q < rx_rings; q++) {
    retval = rte_eth_rx_queue_setup(
        port, q, nb_rxd, rte_eth_dev_socket_id(port), NULL, mbuf_pools[q]);
    if (retval < 0) return retval;
  }

  txconf = dev_info.default_txconf;
  txconf.offloads = port_conf.txmode.offloads;
  /* Allocate and set up 1 TX queue per TX worker port. */
  for (q = 0; q < tx_rings; q++) {
    retval = rte_eth_tx_queue_setup(port, q, nb_txd,
                                    rte_eth_dev_socket_id(port), &txconf);
    if (retval < 0) return retval;
  }

  // Reset all stats.
  retval = rte_eth_stats_reset(port);
  if (retval != 0) return retval;

  retval = rte_eth_xstats_reset(port);
  if (retval != 0) return retval;

  /* Start the port. */
  retval = rte_eth_dev_start(port);
  if (retval < 0) return retval;

  return 0;
}

struct rte_mempool* create_mbuf_pool(unsigned lcore_id) {
  unsigned mbuf_entries = (MBUF_CACHE_SIZE + BURST_SIZE + NUM_SAMPLE_PACKETS);
  mbuf_entries = RTE_MAX(mbuf_entries, (unsigned)MIN_NUM_MBUFS);

  printf("Creating mbuf pool for %u entries for lcore %u\n", mbuf_entries,
         lcore_id);

  /* Creates a new mempool in memory to hold the mbufs. */
  char MBUF_POOL_NAME[20];
  sprintf(MBUF_POOL_NAME, "MBUF_POOL_%u", lcore_id);

  unsigned socket_id = rte_lcore_to_socket_id(lcore_id);

  struct rte_mempool* mbuf_pool =
      rte_pktmbuf_pool_create(MBUF_POOL_NAME, mbuf_entries, MBUF_CACHE_SIZE, 0,
                              RTE_MBUF_DEFAULT_BUF_SIZE, socket_id);

  if (mbuf_pool == NULL) {
    rte_exit(EXIT_FAILURE, "Failed to create mbuf pool\n");
  }

  return mbuf_pool;
}

void wait_to_start() {
  uint64_t last_cnt = config.runtime.update_cnt;
  while (!quit) {
    if (config.runtime.running && (config.runtime.rate_per_core > 0)) {
      break;
    }
    while ((config.runtime.update_cnt == last_cnt) && !quit) {
      std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    last_cnt = config.runtime.update_cnt;
  }
}

static void generate_template_packet(byte_t* pkt) {
  // Initialize Ethernet header
  struct rte_ether_hdr* ether_hdr = (struct rte_ether_hdr*)pkt;

  ether_hdr->src_addr = src_mac;
  ether_hdr->dst_addr = dst_mac;
  ether_hdr->ether_type = rte_cpu_to_be_16(RTE_ETHER_TYPE_IPV4);

  // Initialize the IPv4 header
  struct rte_ipv4_hdr* ip_hdr = (struct rte_ipv4_hdr*)(ether_hdr + 1);

  ip_hdr->version_ihl = RTE_IPV4_VHL_DEF;
  ip_hdr->type_of_service = 0;
  ip_hdr->total_length = 0;
  ip_hdr->packet_id = 0;
  ip_hdr->fragment_offset = 0;
  ip_hdr->time_to_live = 64;
  ip_hdr->next_proto_id = IPPROTO_UDP;
  ip_hdr->hdr_checksum = 0;  // Parameter
  ip_hdr->src_addr = 0;      // Parameter
  ip_hdr->dst_addr = 0;      // Parameter

  // Initialize the UDP header
  struct rte_udp_hdr* udp_hdr = (struct rte_udp_hdr*)(ip_hdr + 1);

  udp_hdr->src_port = 0;  // Parameter
  udp_hdr->dst_port = 0;  // Parameter
  udp_hdr->dgram_cksum = 0;

  // Fill payload with 1s.
  byte_t* payload = (byte_t*)(((char*)udp_hdr) + sizeof(struct rte_udp_hdr));
  bytes_t payload_size = MAX_PKT_SIZE - sizeof(struct rte_ether_hdr) -
                         sizeof(struct rte_ipv4_hdr) -
                         sizeof(struct rte_udp_hdr);
  for (bytes_t i = 0; i < payload_size; ++i) {
    payload[i] = 0xff;
  }
}

static flow_t generate_random_flow() {
  return {(rte_be32_t)(rte_rand() & 0xffffffff),
          (rte_be32_t)(rte_rand() & 0xffffffff),
          (rte_be16_t)(rte_rand() & 0xffff), (rte_be16_t)(rte_rand() & 0xffff)};
}

static std::vector<std::vector<flow_t>> generate_unique_flows_per_worker() {
  struct flow_hash_t {
    size_t operator()(const flow_t& flow) const {
      size_t hash = std::hash<int>()(flow.src_ip);
      hash ^= std::hash<int>()(flow.dst_ip);
      hash ^= std::hash<int>()(flow.src_port);
      hash ^= std::hash<int>()(flow.dst_port);
      return hash;
    }
  };

  struct flow_comp_t {
    bool operator()(const flow_t& f1, const flow_t& f2) const {
      return f1.src_ip == f2.src_ip && f1.dst_ip == f2.dst_ip &&
             f1.src_port == f2.src_port && f1.dst_port == f2.dst_port;
    };
  };

  std::vector<std::vector<flow_t>> flows(config.tx.num_cores);
  std::unordered_set<flow_t, flow_hash_t, flow_comp_t> flows_set;
  std::unordered_set<crc32_t> flows_crc;
  int worker_idx = 0;

  auto crc_mask = (uint32_t)((1 << (uint64_t)(config.crc_bits)) - 1);

  while (flows_set.size() != config.num_flows) {
    printf("Generating flows %lu/%u\r", flows_set.size(), config.num_flows);

    auto flow = generate_random_flow();

    // Already generated. Unlikely, but we still check...
    if (flows_set.find(flow) != flows_set.end()) {
      continue;
    }

    if (config.crc_unique_flows) {
      auto crc = calculate_crc32((byte_t*)&flow, sizeof(flow)) & crc_mask;

      // Although the flow is unique, its masked CRC is not.
      if (flows_crc.find(crc) != flows_crc.end()) {
        continue;
      }

      // We're good.
      flows_crc.insert(crc);
    }

    flows_set.insert(flow);
    flows[worker_idx].push_back(flow);

    // Every worker should only see an even number of flows.
    if (flows_set.size() % 2 == 0) {
      worker_idx = (worker_idx + 1) % config.tx.num_cores;
    }
  }
  printf("Generating flows %lu/%u\n", flows_set.size(), config.num_flows);

  return flows;
}

// Given a desired throughput and (expected) packet size, computes the number of
// TSC ticks per packet burst.
static inline uint64_t compute_ticks_per_burst(rate_gbps_t rate,
                                               bits_t pkt_size) {
  // Traffic-gen is disabled
  if (rate == 0) {
    return 0;
  }

  pkt_size += (20 + 4) * 8;  // CRC and inter-packet gap.
  double packets_per_us = (rate * 1000 / pkt_size);
  uint64_t ticks_per_us = clock_scale();

  // (ticks/us * packets/burst) / (packets/us)
  return (ticks_per_us * BURST_SIZE) / packets_per_us;
}

static int tx_worker_main(void* arg) {
  auto worker_config = (worker_config_t*)arg;

  auto pkt_size_without_crc = worker_config->pkt_size - 4;
  auto num_total_flows = worker_config->flows.size();
  auto num_base_flows = num_total_flows / 2;

  struct rte_mbuf** mbufs = (struct rte_mbuf**)rte_malloc(
      "mbufs", sizeof(struct rte_mbuf*) * NUM_SAMPLE_PACKETS, 0);
  if (mbufs == NULL) {
    rte_exit(EXIT_FAILURE, "Cannot allocate mbufs\n");
  }

  byte_t template_packet[MAX_PKT_SIZE];
  generate_template_packet(template_packet);

  flow_t* base_flows =
      (flow_t*)rte_malloc("base_flows", num_base_flows * sizeof(flow_t), 0);
  flow_t* churn_flows =
      (flow_t*)rte_malloc("churn_flows", num_base_flows * sizeof(flow_t), 0);

  for (uint32_t i = 0; i < num_total_flows; i++) {
    if (i < num_base_flows) {
      base_flows[i] = worker_config->flows[i];
    } else {
      churn_flows[i - num_base_flows] = worker_config->flows[i];
    }
  }

  flow_t* flows[2] = {base_flows, churn_flows};

  // Prefill buffers with template packet.
  for (uint32_t i = 0; i < NUM_SAMPLE_PACKETS; i++) {
    mbufs[i] = rte_pktmbuf_alloc(worker_config->pool);

    if (unlikely(mbufs[i] == nullptr)) {
      rte_exit(EXIT_FAILURE, "Failed to create mbuf\n");
    }

    struct rte_ether_hdr* ether_hdr = (struct rte_ether_hdr*)template_packet;
    struct rte_ipv4_hdr* ip_hdr = (struct rte_ipv4_hdr*)(ether_hdr + 1);

    ip_hdr->total_length =
        rte_cpu_to_be_16(pkt_size_without_crc - sizeof(struct rte_ether_hdr));

    rte_pktmbuf_append(mbufs[i], pkt_size_without_crc);
    rte_memcpy(rte_pktmbuf_mtod(mbufs[i], void*), template_packet,
               pkt_size_without_crc);
  }

  printf("Lcore %u is ready.\n", rte_lcore_id());
  wait_to_start();

  auto chosen_flows_idxs = std::vector<uint8_t>(num_base_flows);
  auto flows_timers = std::vector<ticks_t>(num_base_flows);
  auto flows_offsets = std::vector<ticks_t>(num_base_flows);

  // Triger clock scale calculation beforehand, as it pauses the execution for 1
  // second.
  clock_scale();

  uint64_t last_update_cnt = 0;

  // Rate-limiting
  ticks_t ticks_per_burst = compute_ticks_per_burst(
      worker_config->runtime->rate_per_core, (worker_config->pkt_size * 8));

  // Rate control
  ticks_t period_end_tick;
  ticks_t first_tick = TscClock::now();
  ticks_t period_start_tick = TscClock::now();

  ticks_t elapsed_ticks = 0;
  uint32_t mbuf_burst_offset = 0;

  bytes_t total_pkt_size = 0;
  uint64_t num_total_tx = 0;

  ticks_t flow_ticks = worker_config->runtime->flow_ttl * clock_scale() / 1000;

  auto queue_id = worker_config->queue_id;

  for (uint32_t i = 0; i < num_base_flows; i++) {
    // Spreading out the churn, to avoid bursty churn.
    flows_timers[i] = first_tick + rte_rand() % flow_ticks;
    chosen_flows_idxs[i] = 0;
  }

  // Run until the application is killed
  while (likely(!quit)) {
    if (unlikely(worker_config->runtime->update_cnt > last_update_cnt)) {
      elapsed_ticks += TscClock::now() - first_tick;
      wait_to_start();

      last_update_cnt = worker_config->runtime->update_cnt;
      ticks_per_burst = compute_ticks_per_burst(
          worker_config->runtime->rate_per_core, worker_config->pkt_size * 8);
      flow_ticks = worker_config->runtime->flow_ttl * clock_scale() / 1000;
      first_tick = TscClock::now();

      for (uint32_t i = 0; i < num_base_flows; i++) {
        // Spreading out the churn, to avoid bursty churn.
        flows_timers[i] = first_tick + rte_rand() % flow_ticks;
        chosen_flows_idxs[i] = 0;
      }
    }

    period_end_tick = (period_start_tick + ticks_per_burst);

    rte_mbuf** mbuf_burst = mbufs + mbuf_burst_offset;
    mbuf_burst_offset = (mbuf_burst_offset + BURST_SIZE) % NUM_SAMPLE_PACKETS;

    // Generate a burst of packets
    for (unsigned i = 0; i < BURST_SIZE; i++) {
      rte_mbuf* pkt = mbuf_burst[i];
      total_pkt_size += pkt->pkt_len;

      struct rte_ether_hdr* ether_hdr =
          rte_pktmbuf_mtod(pkt, struct rte_ether_hdr*);
      struct rte_ipv4_hdr* ip_hdr = (struct rte_ipv4_hdr*)(ether_hdr + 1);
      struct rte_udp_hdr* udp_hdr = (struct rte_udp_hdr*)(ip_hdr + 1);

      uint32_t flow_idx = (mbuf_burst_offset + i) % num_base_flows;

      auto& chosen_flows_idx = chosen_flows_idxs[flow_idx];
      auto& timer = flows_timers[flow_idx];

      if (period_start_tick >= timer) {
        timer += flow_ticks;
        chosen_flows_idx = (chosen_flows_idx + 1) % 2;
      }

      auto chosen_flows = flows[chosen_flows_idx];

      ip_hdr->src_addr = chosen_flows[flow_idx].src_ip;
      ip_hdr->dst_addr = chosen_flows[flow_idx].dst_ip;
      udp_hdr->src_port = chosen_flows[flow_idx].src_port;
      udp_hdr->dst_port = chosen_flows[flow_idx].dst_port;

      // HACK(sadok): Increase refcnt to avoid freeing.
      pkt->refcnt = MIN_NUM_MBUFS;
    }

    uint16_t num_tx =
        rte_eth_tx_burst(config.tx.port, queue_id, mbuf_burst, BURST_SIZE);

    num_total_tx += num_tx;

    while ((period_start_tick = TscClock::now()) < period_end_tick) {
      // prevent the compiler from removing this loop
      __asm__ __volatile__("");
    }
  }

  rte_free(mbufs);
  rte_free(base_flows);
  rte_free(churn_flows);

  return 0;
}

int main(int argc, char* argv[]) {
  quit = false;

  signal(SIGINT, signal_handler);
  signal(SIGTERM, signal_handler);

  /* Initialize the Environment Abstraction Layer (EAL). */
  int ret = rte_eal_init(argc, argv);
  if (ret < 0) {
    rte_exit(EXIT_FAILURE, "Error with EAL initialization\n");
  }
  argc -= ret;
  argv += ret;

  // Parse command-line arguments
  config_init(argc, argv);
  config_print();

  struct rte_mempool** mbufs_pools = (struct rte_mempool**)rte_malloc(
      "mbufs pools", sizeof(struct rte_mempool*) * config.tx.num_cores, 0);

  for (unsigned i = 0; i < config.tx.num_cores; i++) {
    unsigned lcore_id = config.tx.cores[i];
    mbufs_pools[i] = create_mbuf_pool(lcore_id);
  }

  /* Initialize all ports. */
  if (port_init(config.rx.port, 1, 1, mbufs_pools))
    rte_exit(EXIT_FAILURE, "Cannot init rx port %" PRIu16 "\n", 0);

  if (port_init(config.tx.port, 0, config.tx.num_cores, mbufs_pools))
    rte_exit(EXIT_FAILURE, "Cannot init tx port %" PRIu16 "\n", 0);

  auto flows_per_worker = generate_unique_flows_per_worker();

  for (unsigned i = 0; i < config.tx.num_cores; i++) {
    unsigned lcore_id = config.tx.cores[i];
    unsigned queue_id = i;
    worker_config_t* worker_config =
        new worker_config_t(mbufs_pools[i], queue_id, config.pkt_size,
                            flows_per_worker[i], &config.runtime);
    rte_eal_remote_launch(tx_worker_main, (void*)worker_config, lcore_id);
  }

  // We no longer need the arrays. This doesn't free the mbufs themselves
  // though, we still need them.
  rte_free(mbufs_pools);

  // pktgen_cmdline();

  printf("Waiting for workers...\n");
  std::this_thread::sleep_for(std::chrono::seconds(1));

  rate_mbps_t rate = 50000;
  churn_fpm_t churn = 1000000;

  printf("Trying %.2lf Mbps rate churn %lu fpm...\n", rate, churn);

  pktgen_rate(rate / 1e3);
  pktgen_churn(churn);
  pktgen_start();
  printf("Running experiment...\n");
  std::this_thread::sleep_for(std::chrono::seconds(10));
  pktgen_stop();

  quit = true;

  printf("Waiting for workers to finish...\n");

  // Wait for all processes to complete
  rte_eal_mp_wait_lcore();

  pktgen_stats_display(config.rx.port);
  // pktgen_stats_display(config.tx.port);

  struct rte_eth_stats stats;
  const uint16_t port_id = config.rx.port;

  rte_eth_stats_get(port_id, &stats);

  uint64_t rx_unicast_packets_stat_id;
  uint64_t rx_unicast_packets;
  if (rte_eth_xstats_get_id_by_name(config.rx.port, "rx_unicast_packets",
                                    &rx_unicast_packets_stat_id) != 0) {
    printf("xstats error\n");
    exit(1);
  }
  if (rte_eth_xstats_get_by_id(config.rx.port, &rx_unicast_packets_stat_id,
                               &rx_unicast_packets, 1) < 0) {
    printf("xstats error\n");
    exit(1);
  }

  printf("\n==== Statistics ====\n");
  printf("Port %" PRIu8 "\n", port_id);
  printf("    ipackets: %" PRIu64 "\n", stats.ipackets);
  printf("    ibytes:   %" PRIu64 "\n", stats.ibytes);
  printf("    unicast:  %" PRIu64 "\n", rx_unicast_packets);
  printf("    *ibytes:  %" PRIu64 "\n",
         rx_unicast_packets * (MIN_PKT_SIZE + 20) * 8);
  printf("    Mbps:     %.2lf\n", ((double)(stats.ibytes * 8) / 1e6) / 10);
  printf("    *Mbps:    %.2lf\n",
         ((double)rx_unicast_packets * ((MIN_PKT_SIZE + 20) * 8) / 1e6) / 10);
  printf("    Mpps:     %.2lf\n", ((double)rx_unicast_packets / 1e6) / 10);

  rte_eal_cleanup();

  return 0;
}