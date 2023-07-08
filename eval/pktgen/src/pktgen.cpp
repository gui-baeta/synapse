#include "pktgen.h"

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

#include "tsc_clock.h"

// DPDK-related macros
#define BURST_SIZE 32
#define MBUF_CACHE_SIZE 512
#define MIN_NUM_MBUFS 8192
#define DESC_RING_SIZE 1024

volatile bool quit;

static void signal_handler(int signum) {
  (void)signum;
  quit = true;
}

void pktgen_stats_display() {
  struct rte_eth_stats stats;

  const uint16_t port_id = 0;
  constexpr uint16_t kMaxNbStats = 1024;

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
  struct rte_eth_xstat xstats[kMaxNbStats];
  if (rte_eth_xstats_get(port_id, xstats, num_xstats) != num_xstats) {
    printf("Cannot get xstats\n");
  }
  struct rte_eth_xstat_name xstats_names[kMaxNbStats];
  if (rte_eth_xstats_get_names(port_id, xstats_names, num_xstats) !=
      num_xstats) {
    printf("Cannot get xstats\n");
  }
  for (int i = 0; i < num_xstats; ++i) {
    printf("%s: %" PRIu64 "\n", xstats_names[i].name, xstats[i].value);
  }
  printf("\n");
}

int main(int argc, char* argv[]) {
  // struct rte_mempool* mbuf_pool;

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

  rte_eal_cleanup();
  return 0;

  // unsigned mbuf_entries =
  //     (MBUF_CACHE_SIZE + (3 * BURST_SIZE) + (8 * DESC_RING_SIZE));

  // mbuf_entries = RTE_MAX(mbuf_entries, (unsigned)MIN_NUM_MBUFS);
  // /* Creates a new mempool in memory to hold the mbufs. */
  // mbuf_pool =
  //     rte_pktmbuf_pool_create("MBUF_POOL", mbuf_entries, MBUF_CACHE_SIZE, 0,
  //                             RTE_MBUF_DEFAULT_BUF_SIZE, rte_socket_id());

  // if (mbuf_pool == NULL) rte_exit(EXIT_FAILURE, "Failed to create mbuf
  // pool\n");

  // /* Initialize all ports. */
  // if (port_init(0, mbuf_pool))
  //   rte_exit(EXIT_FAILURE, "Cannot init port %" PRIu16 "\n", 0);

  // // Create the configurations
  // worker_conf* confs[3];
  // uint16_t attack_queue_id = 0;
  // uint16_t innocent_queue_id = 1;
  // uint16_t innocent_ooo_queue_id = 2;

  // // Attacker sends every other packet.
  // uint32_t attack_seq_offset = kAttackPayloadSize * 2;

  // // Innocent users send all payloads.
  // uint32_t innocent_seq_offset = kInnocentPayloadSize;
  // uint32_t innocent_ooo_seq_offset = kInnocentOooPayloadSize;

  // confs[PacketClass::ATTACK] = new worker_conf(
  //     mbuf_pool, PacketClass::ATTACK, &pktgen_config.attack_rate_gbps,
  //     kAttackPacketSizeInBytes, attack_queue_id, attack_seq_offset,
  //     kNumAttackFlows, kAttackSrcPort, kAttackRecoveryWindow);

  // confs[PacketClass::INNOCENT] = new worker_conf(
  //     mbuf_pool, PacketClass::INNOCENT, &pktgen_config.innocent_rate_gbps,
  //     kInnocentPacketSizeInBytes, innocent_queue_id, innocent_seq_offset,
  //     kNumInnocentFlows, kInnocentSrcPort, kInnocentRecoveryWindow);

  // confs[PacketClass::INNOCENT_OOO] = new worker_conf(
  //     mbuf_pool, PacketClass::INNOCENT_OOO,
  //     &pktgen_config.innocent_ooo_rate_gbps, kInnocentOooPacketSizeInBytes,
  //     innocent_ooo_queue_id, innocent_ooo_seq_offset, kNumInnocentOooFlows,
  //     kInnocentOooSrcPort, kInnocentOooRecoveryWindow);

  // // Run the worker process
  // unsigned idx = 0;
  // unsigned lcore_id;
  // RTE_LCORE_FOREACH_SLAVE(lcore_id) {
  //   rte_eal_remote_launch(lcore_worker, (void*)confs[idx], lcore_id);
  //   idx++;
  // }

  // pktgen_cmdline();
  // quit = true;

  // std::cout << "Waiting for workers to finish..." << std::endl;

  // // Wait for all processes to complete
  // rte_eal_mp_wait_lcore();

  // pktgen_stats_display();

  // rte_eal_cleanup();

  return 0;
}