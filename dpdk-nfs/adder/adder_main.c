#include "adder_config.h"
#include "nf-util.h"
#include "nf.h"

#ifdef KLEE_VERIFICATION
#include "lib/models/str-descr.h"
#endif  // KLEE_VERIFICATION

struct nf_config config;

bool nf_init(void) { return true; }

struct custom_chunk_t {
  uint8_t a;
  uint8_t b;
  uint8_t c;
  uint8_t d;
  uint8_t e;
  uint8_t f;
  uint8_t g;
  uint8_t h;
  uint8_t i;
  uint8_t j;
  uint8_t result;
};

#ifdef KLEE_VERIFICATION
static struct str_field_descr custom_chunk_fields[] = {
    {offsetof(struct custom_chunk_t, a), sizeof(uint8_t), 0, "a"},
    {offsetof(struct custom_chunk_t, b), sizeof(uint8_t), 0, "b"},
    {offsetof(struct custom_chunk_t, c), sizeof(uint8_t), 0, "c"},
    {offsetof(struct custom_chunk_t, d), sizeof(uint8_t), 0, "d"},
    {offsetof(struct custom_chunk_t, e), sizeof(uint8_t), 0, "e"},
    {offsetof(struct custom_chunk_t, f), sizeof(uint8_t), 0, "f"},
    {offsetof(struct custom_chunk_t, g), sizeof(uint8_t), 0, "g"},
    {offsetof(struct custom_chunk_t, h), sizeof(uint8_t), 0, "h"},
    {offsetof(struct custom_chunk_t, i), sizeof(uint8_t), 0, "i"},
    {offsetof(struct custom_chunk_t, j), sizeof(uint8_t), 0, "j"},
    {offsetof(struct custom_chunk_t, result), sizeof(uint8_t), 0, "result"},
};
#endif

struct custom_chunk_t *parse_custom_chunk(uint8_t **buffer) {
  uint16_t unread_len = packet_get_unread_length(buffer);
  size_t required_size = sizeof(struct custom_chunk_t);

  if (unread_len < required_size) {
    return NULL;
  }

#ifdef KLEE_VERIFICATION
  CHUNK_LAYOUT(buffer, custom_chunk_t, custom_chunk_fields);
#endif

  void *hdr = nf_borrow_next_chunk(buffer, sizeof(struct custom_chunk_t));
  return (struct custom_chunk_t *)hdr;
}

struct custom_chunk_t *parse_custom_secret_chunk(uint8_t **buffer) {
  uint16_t unread_len = packet_get_unread_length(buffer);
  size_t required_size = sizeof(struct custom_chunk_t);

  if (unread_len < required_size) {
    return NULL;
  }

#ifdef KLEE_VERIFICATION
  CHUNK_LAYOUT(buffer, custom_chunk_t, custom_chunk_fields);
#endif

  void *hdr = nf_borrow_next_secret(buffer, sizeof(struct custom_chunk_t));
  return (struct custom_chunk_t *)hdr;
}

int nf_process(uint16_t device, uint8_t **buffer, uint16_t packet_length,
               vigor_time_t now, struct rte_mbuf *mbuf) {
  // Mark now as unused, we don't care about time
  (void)now;

//  struct rte_ether_hdr *rte_ether_header = nf_then_get_rte_ether_header(buffer);
//  struct custom_chunk_t *our_custom_chunk = parse_custom_chunk(buffer);
  struct custom_chunk_t *secret_chunk = parse_custom_secret_chunk(buffer);

//  if (our_custom_chunk != NULL &&
//      our_custom_chunk->a <= UINT32_MAX - our_custom_chunk->b) {
//    our_custom_chunk->c = our_custom_chunk->a + our_custom_chunk->b;
//  }
//  if (secret_chunk != NULL &&
//      secret_chunk->a <= UINT32_MAX - secret_chunk->b) {

//    for (int i = 0; i < 3; i++) {
//      secret_chunk->c += 1;
//    }

    if a && b > 50 // if man && age > 50 years
    if !a && b > 60 // if woman && age > 60 years
    if c // if smoking
    if d // if diabetic
    if e // if high blood pressure
    if f < 40 // if HDL cholesterol < 40
    if g > h - 90 // if weight > height - 90
    if i < 30 // if daily physical activity < 30
    if a && j > 3 // if man && alcohol cons. > 3 glasses/day
    if !a && j > 2 // if !man && alcohol cons. > 2 glasses/day

    if (secret_chunk->a > 3) {
        secret_chunk->c += 3;
    }


    if (secret_chunk->c > 5) {
        secret_chunk->c += 1;
    }


    if (secret_chunk->b > 2) {
        secret_chunk->c += 2;
    }

//    if (secret_chunk->a > 5 && secret_chunk->b > 2) {
//      secret_chunk->c += 1;
//    secret_chunk->a += 3 + + secret_chunk->b + secret_chunk->c;
//    } else {
//      secret_chunk->c *= 2;
//    }
//  }
//  uint16_t dst_device;
//  if (device == config.wan_device) {
//    dst_device = config.lan_device;
//  } else {
//    dst_device = config.wan_device;
//  }

  return 0;
}
