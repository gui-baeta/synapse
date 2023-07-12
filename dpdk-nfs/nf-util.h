#pragma once

#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#include <rte_byteorder.h>
#include <rte_common.h>
#include <rte_ethdev.h>
#include <rte_ip.h>
#include <rte_mbuf.h>
#include <rte_tcp.h>
#include <rte_udp.h>

#include "lib/verified/packet-io.h"
#include "lib/verified/tcpudp_hdr.h"

#ifdef KLEE_VERIFICATION
#include "lib/models/str-descr.h"
#include "lib/models/verified/packet-io-control.h"
#include <rte_ether.h>
#endif  // KLEE_VERIFICATION

// rte_ether
struct rte_ether_addr;
struct rte_ether_hdr;

#define IP_MIN_SIZE_WORDS 5
#define WORD_SIZE 4

#ifdef KLEE_VERIFICATION
static struct str_field_descr rte_ether_fields[] = {
    {offsetof(struct rte_ether_hdr, ether_type), sizeof(uint16_t), 0,
     "ether_type"},
    {offsetof(struct rte_ether_hdr, d_addr), sizeof(struct rte_ether_addr), 0,
     "d_addr"},
    {offsetof(struct rte_ether_hdr, s_addr), sizeof(struct rte_ether_addr), 0,
     "s_addr"}};
static struct str_field_descr rte_ipv4_fields[] = {
    {offsetof(struct rte_ipv4_hdr, version_ihl), sizeof(uint8_t), 0,
     "version_ihl"},
    {offsetof(struct rte_ipv4_hdr, type_of_service), sizeof(uint8_t), 0,
     "type_of_service"},
    {offsetof(struct rte_ipv4_hdr, total_length), sizeof(uint16_t), 0,
     "total_length"},
    {offsetof(struct rte_ipv4_hdr, packet_id), sizeof(uint16_t), 0,
     "packet_id"},
    {offsetof(struct rte_ipv4_hdr, fragment_offset), sizeof(uint16_t), 0,
     "fragment_offset"},
    {offsetof(struct rte_ipv4_hdr, time_to_live), sizeof(uint8_t), 0,
     "time_to_live"},
    {offsetof(struct rte_ipv4_hdr, next_proto_id), sizeof(uint8_t), 0,
     "next_proto_id"},
    {offsetof(struct rte_ipv4_hdr, hdr_checksum), sizeof(uint16_t), 0,
     "hdr_checksum"},
    {offsetof(struct rte_ipv4_hdr, src_addr), sizeof(uint32_t), 0, "src_addr"},
    {offsetof(struct rte_ipv4_hdr, dst_addr), sizeof(uint32_t), 0, "dst_addr"}};
static struct str_field_descr tcpudp_fields[] = {
    {offsetof(struct tcpudp_hdr, src_port), sizeof(uint16_t), 0, "src_port"},
    {offsetof(struct tcpudp_hdr, dst_port), sizeof(uint16_t), 0, "dst_port"}};
static struct str_field_descr tcp_fields[] = {
    {offsetof(struct rte_tcp_hdr, src_port), sizeof(uint16_t), 0, "src_port"},
    {offsetof(struct rte_tcp_hdr, dst_port), sizeof(uint16_t), 0, "dst_port"},
    {offsetof(struct rte_tcp_hdr, sent_seq), sizeof(uint32_t), 0, "seq_no"},
    {offsetof(struct rte_tcp_hdr, recv_ack), sizeof(uint32_t), 0, "ack_no"},
    {offsetof(struct rte_tcp_hdr, data_off), sizeof(uint8_t), 0, "data_off"},
    {offsetof(struct rte_tcp_hdr, tcp_flags), sizeof(uint8_t), 0, "flags"},
    {offsetof(struct rte_tcp_hdr, rx_win), sizeof(uint16_t), 0, "window"},
    {offsetof(struct rte_tcp_hdr, cksum), sizeof(uint16_t), 0, "checksum"},
    {offsetof(struct rte_tcp_hdr, tcp_urp), sizeof(uint16_t), 0, "urgent_ptr"},
};
static struct str_field_descr udp_fields[] = {
    {offsetof(struct rte_udp_hdr, src_port), sizeof(uint16_t), 0, "src_port"},
    {offsetof(struct rte_udp_hdr, dst_port), sizeof(uint16_t), 0, "dst_port"},
    {offsetof(struct rte_udp_hdr, dgram_len), sizeof(uint16_t), 0, "length"},
    {offsetof(struct rte_udp_hdr, dgram_cksum), sizeof(uint16_t), 0,
     "checksum"},
};
static struct nested_field_descr rte_ether_nested_fields[] = {
    {offsetof(struct rte_ether_hdr, d_addr), 0, sizeof(uint8_t), 6,
     "src_addr_bytes"},
    {offsetof(struct rte_ether_hdr, s_addr), 0, sizeof(uint8_t), 6,
     "dst_addr_bytes"}};
#endif  // KLEE_VERIFICATION

void nf_log_pkt(struct rte_ether_hdr *rte_ether_header,
                struct rte_ipv4_hdr *rte_ipv4_header,
                struct tcpudp_hdr *tcpudp_header);

bool nf_has_rte_ipv4_header(struct rte_ether_hdr *header);
bool nf_has_tcpudp_header(struct rte_ipv4_hdr *header);
bool nf_has_tcp_header(struct rte_ipv4_hdr *header);
bool nf_has_udp_header(struct rte_ipv4_hdr *header);

void nf_set_rte_ipv4_udptcp_checksum(struct rte_ipv4_hdr *ip_header,
                                     void *l4_header, void *packet);

uintmax_t nf_util_parse_int(const char *str, const char *name, int base,
                            char next);

char *nf_mac_to_str(struct rte_ether_addr *addr);

char *nf_rte_ipv4_to_str(uint32_t addr);

#define MAX_N_CHUNKS 100
extern void *chunks_borrowed[];
extern size_t chunks_borrowed_num;

static inline void *nf_borrow_next_chunk(uint8_t **p, size_t length) {
  assert(chunks_borrowed_num < MAX_N_CHUNKS);
  void *chunk;
  packet_borrow_next_chunk(*p, length, &chunk);
  chunks_borrowed[chunks_borrowed_num] = chunk;
  chunks_borrowed_num++;
  return chunk;
}

#ifdef KLEE_VERIFICATION
#define CHUNK_LAYOUT_IMPL(pkt, len, fields, n_fields, nests, n_nests, tag) \
  packet_set_next_chunk_layout(pkt, len, fields, n_fields, nests, n_nests, tag)
#else  // KLEE_VERIFICATION
#define CHUNK_LAYOUT_IMPL(pkt, len, fields, n_fields, nests, n_nests, \
                          tag) /*nothing*/
#endif                         // KLEE_VERIFICATION

#define CHUNK_LAYOUT_N(pkt, str_name, fields, nests)           \
  CHUNK_LAYOUT_IMPL(pkt, sizeof(struct str_name), fields,      \
                    sizeof(fields) / sizeof(fields[0]), nests, \
                    sizeof(nests) / sizeof(nests[0]), #str_name);

#define CHUNK_LAYOUT(pkt, str_name, fields)               \
  CHUNK_LAYOUT_IMPL(pkt, sizeof(struct str_name), fields, \
                    sizeof(fields) / sizeof(fields[0]), NULL, 0, #str_name);

static inline void *nf_shrink_chunk(uint8_t **p, size_t length,
                                    struct rte_mbuf *mbuf) {
  assert(chunks_borrowed_num < MAX_N_CHUNKS);
  assert(chunks_borrowed_num);
  packet_shrink_chunk((void **)p, length, chunks_borrowed, chunks_borrowed_num,
                      mbuf);
  return chunks_borrowed[chunks_borrowed_num - 1];
}

static inline void *nf_insert_new_chunk(uint8_t **p, size_t length,
                                        struct rte_mbuf *mbuf) {
  assert(chunks_borrowed_num < MAX_N_CHUNKS);
  assert(chunks_borrowed_num);

  // Do not really trace the ip options chunk, as it's length
  // is unknown statically
  CHUNK_LAYOUT_IMPL(*p, 1, NULL, 0, NULL, 0, "new_hdr");
  packet_insert_new_chunk((void **)p, length, chunks_borrowed,
                          &chunks_borrowed_num, mbuf);

  return chunks_borrowed[chunks_borrowed_num - 1];
}

static inline void *nf_get_borrowed_chunk(uint32_t chunk_i) {
  assert(chunk_i < chunks_borrowed_num);
  return chunks_borrowed[chunk_i];
}

static inline void nf_return_all_chunks(void *p) {
  while (chunks_borrowed_num != 0) {
    packet_return_chunk(p, chunks_borrowed[chunks_borrowed_num - 1]);
    chunks_borrowed_num--;
  }
}

static inline void nf_return_chunk(uint8_t **p) {
  if (chunks_borrowed_num != 0) {
    packet_return_chunk(*p, chunks_borrowed[chunks_borrowed_num - 1]);
    chunks_borrowed_num--;
  }
}

static inline struct rte_ether_hdr *nf_then_get_rte_ether_header(uint8_t **p) {
  CHUNK_LAYOUT_N(*p, rte_ether_hdr, rte_ether_fields, rte_ether_nested_fields);
  void *hdr = nf_borrow_next_chunk(p, sizeof(struct rte_ether_hdr));
  return (struct rte_ether_hdr *)hdr;
}

static inline struct rte_ipv4_hdr *nf_then_get_rte_ipv4_header(
    void *rte_ether_header_, uint8_t **p) {
  struct rte_ether_hdr *rte_ether_header =
      (struct rte_ether_hdr *)rte_ether_header_;

  uint16_t unread_len = packet_get_unread_length(p);
  if ((!nf_has_rte_ipv4_header(rte_ether_header)) |
      (unread_len < sizeof(struct rte_ipv4_hdr))) {
    return NULL;
  }

  CHUNK_LAYOUT(p, rte_ipv4_hdr, rte_ipv4_fields);
  struct rte_ipv4_hdr *hdr = (struct rte_ipv4_hdr *)nf_borrow_next_chunk(
      p, sizeof(struct rte_ipv4_hdr));

  return hdr;
}

static inline struct rte_ipv4_hdr *nf_then_get_rte_ipv4_header_with_options(
    void *rte_ether_header_, uint8_t **p, uint8_t **ip_options) {
  struct rte_ether_hdr *rte_ether_header =
      (struct rte_ether_hdr *)rte_ether_header_;
  *ip_options = NULL;

  uint16_t unread_len = packet_get_unread_length(p);
  if ((!nf_has_rte_ipv4_header(rte_ether_header)) |
      (unread_len < sizeof(struct rte_ipv4_hdr))) {
    return NULL;
  }

  CHUNK_LAYOUT(p, rte_ipv4_hdr, rte_ipv4_fields);
  struct rte_ipv4_hdr *hdr = (struct rte_ipv4_hdr *)nf_borrow_next_chunk(
      p, sizeof(struct rte_ipv4_hdr));

  uint8_t ihl = hdr->version_ihl & 0x0f;
  if ((ihl < IP_MIN_SIZE_WORDS) |
      (unread_len < rte_be_to_cpu_16(hdr->total_length))) {
    return NULL;
  }
  uint16_t ip_options_length = (ihl - IP_MIN_SIZE_WORDS) * WORD_SIZE;
  if ((ip_options_length != 0) &
      (unread_len - sizeof(struct rte_ipv4_hdr) >= ip_options_length)) {
    // Do not really trace the ip options chunk, as it's length
    // is unknown statically
    CHUNK_LAYOUT_IMPL(*p, 1, NULL, 0, NULL, 0, "ipv4_options");
    *ip_options = (uint8_t *)nf_borrow_next_chunk(p, ip_options_length);
  }
  return hdr;
}

static inline struct tcpudp_hdr *nf_then_get_tcpudp_header(
    struct rte_ipv4_hdr *ip_header, uint8_t **p) {
  if ((!nf_has_tcpudp_header(ip_header)) |
      (packet_get_unread_length(p) < sizeof(struct tcpudp_hdr))) {
    return NULL;
  }
  CHUNK_LAYOUT(*p, tcpudp_hdr, tcpudp_fields);
  return (struct tcpudp_hdr *)nf_borrow_next_chunk(p,
                                                   sizeof(struct tcpudp_hdr));
}

static inline struct rte_tcp_hdr *nf_then_get_tcp_header(
    struct rte_ipv4_hdr *ip_header, uint8_t **p) {
  if ((!nf_has_tcp_header(ip_header)) |
      (packet_get_unread_length(p) < sizeof(struct rte_tcp_hdr))) {
    return NULL;
  }
  CHUNK_LAYOUT(*p, rte_tcp_hdr, tcp_fields);
  return (struct rte_tcp_hdr *)nf_borrow_next_chunk(p,
                                                    sizeof(struct rte_tcp_hdr));
}

static inline struct rte_udp_hdr *nf_then_get_udp_header(
    struct rte_ipv4_hdr *ip_header, uint8_t **p) {
  if ((!nf_has_udp_header(ip_header)) |
      (packet_get_unread_length(p) < sizeof(struct rte_udp_hdr))) {
    return NULL;
  }
  CHUNK_LAYOUT(*p, rte_udp_hdr, udp_fields);
  return (struct rte_udp_hdr *)nf_borrow_next_chunk(p,
                                                    sizeof(struct rte_udp_hdr));
}
