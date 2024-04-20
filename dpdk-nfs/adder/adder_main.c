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

  uint8_t _result = 0;

//    //    if a && b > 5 // if man && age(/10) > 50(/10) years
//    if (secret_chunk->a && secret_chunk->b > 5) {
//        secret_chunk->result += 1;
//    }
//
//    // if !a && b > 6 // if woman && age(/10) > 60(/10) years
//    if (!(secret_chunk->a) && secret_chunk->b > 6) {
//        secret_chunk->result += 1;
//    }
//    // if c // if smoking
//    if (secret_chunk->c) {
//        _result += 1;
//    }
//    // if d // if diabetic
//    if (secret_chunk->d) {
//        _result += 1;
//    }
//    // if e // if high blood pressure
//    if (secret_chunk->e) {
//        _result += 1;
//    }
    // if f < 4 // if HDL cholesterol(/10) < 40(/10)
//values = [1,2,0,0,0,5,7,9,12,2,0,0]
//          a b c d e f g h  i j l result
    if (secret_chunk->f < 4) { // false
        _result += 1;
    }
    // if g > h - 6 // if weight(/10) > height(/15) - 90(/15)
    if (secret_chunk->g + 6 > secret_chunk->h) { // true
        _result += 1;
    }
    // if i < 6 // if daily physical activity(/5) < 30(/5)
    if (secret_chunk->i < 6) { // false
        _result += 1;
    }
    // if a && j > 3 // if man && alcohol cons. > 3 glasses/day
    if (secret_chunk->a && secret_chunk->j > 3) { // true and false -> false
        _result += 1;
    }

    secret_chunk->result = _result;
//    // if !a && j > 2 // if !man && alcohol cons. > 2 glasses/day
//    if (!(secret_chunk->a) && secret_chunk->j > 2) {
//        secret_chunk->result += 1;
//    }


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
