
bool flow_eq(void* a, void* b) ;
uint32_t flow_hash(void* obj) ;
void flow_allocate(void* obj) ;
uint32_t client_hash(void* obj) ;
struct Map* map;
struct Vector* vector;
struct DoubleChain* dchain;
struct Sketch* sketch;

bool nf_init() {
  int map_allocation_succeeded__1 = map_allocate(flow_eq, flow_hash, 65536u, &map);

  // 113
  // 114
  // 115
  // 116
  if (map_allocation_succeeded__1) {
    int vector_alloc_success__4 = vector_allocate(16u, 65536u, flow_allocate, &vector);

    // 113
    // 114
    // 115
    if (vector_alloc_success__4) {
      int is_dchain_allocated__7 = dchain_allocate(65536u, &dchain);

      // 113
      // 114
      if (is_dchain_allocated__7) {
        int sketch_allocation_succeeded__10 = sketch_allocate(client_hash, 1024u, 64u, &sketch);

        // 113
        if (sketch_allocation_succeeded__10) {
          return 1;
        }

        // 114
        else {
          return 0;
        } // !sketch_allocation_succeeded__10

      }

      // 115
      else {
        return 0;
      } // !is_dchain_allocated__7

    }

    // 116
    else {
      return 0;
    } // !vector_alloc_success__4

  }

  // 117
  else {
    return 0;
  } // !map_allocation_succeeded__1

}

int nf_process(uint16_t device, uint8_t* packet, uint16_t packet_length, int64_t now) {
  struct rte_ether_hdr* ether_header_1 = (struct rte_ether_hdr*)(packet);

  // 119
  // 120
  // 121
  // 122
  // 123
  // 124
  if (0u == ((8u != ether_header_1->ether_type) | ((4294967282u + packet_length) < 20ul))) {
    struct rte_ipv4_hdr* ipv4_header_1 = (struct rte_ipv4_hdr*)(packet + 14u);

    // 119
    // 120
    // 121
    // 122
    // 123
    if (0u == ((0u == ((6u == ipv4_header_1->next_proto_id) | (17u == ipv4_header_1->next_proto_id))) | ((4294967262u + packet_length) < 4ul))) {
      struct tcpudp_hdr* tcpudp_header_1 = (struct tcpudp_hdr*)(packet + (14u + 20u));
      int number_of_freed_flows__36 = expire_items_single_map(dchain, vector, map, now - 100000000000ul);
      sketch_expire(sketch, now - 100000000000ul);

      // 119
      if (device) {
        return 0;
      }

      // 120
      // 121
      // 122
      // 123
      else {
        uint8_t map_key[13];
        map_key[0u] = tcpudp_header_1->src_port & 0xff;
        map_key[1u] = (tcpudp_header_1->src_port >> 8) & 0xff;
        map_key[2u] = tcpudp_header_1->dst_port & 0xff;
        map_key[3u] = (tcpudp_header_1->dst_port >> 8) & 0xff;
        map_key[4u] = ipv4_header_1->src_addr & 0xff;
        map_key[5u] = (ipv4_header_1->src_addr >> 8) & 0xff;
        map_key[6u] = (ipv4_header_1->src_addr >> 16) & 0xff;
        map_key[7u] = (ipv4_header_1->src_addr >> 24) & 0xff;
        map_key[8u] = ipv4_header_1->dst_addr & 0xff;
        map_key[9u] = (ipv4_header_1->dst_addr >> 8) & 0xff;
        map_key[10u] = (ipv4_header_1->dst_addr >> 16) & 0xff;
        map_key[11u] = (ipv4_header_1->dst_addr >> 24) & 0xff;
        map_key[12u] = ipv4_header_1->next_proto_id;
        int map_value_out;
        int map_has_this_key__48 = map_get(map, &map_key, &map_value_out);
        uint8_t sketch_key[8];
        sketch_key[0u] = ipv4_header_1->src_addr & 0xff;
        sketch_key[1u] = (ipv4_header_1->src_addr >> 8) & 0xff;
        sketch_key[2u] = (ipv4_header_1->src_addr >> 16) & 0xff;
        sketch_key[3u] = (ipv4_header_1->src_addr >> 24) & 0xff;
        sketch_key[4u] = ipv4_header_1->dst_addr & 0xff;
        sketch_key[5u] = (ipv4_header_1->dst_addr >> 8) & 0xff;
        sketch_key[6u] = (ipv4_header_1->dst_addr >> 16) & 0xff;
        sketch_key[7u] = (ipv4_header_1->dst_addr >> 24) & 0xff;
        sketch_compute_hashes(sketch, &sketch_key);

        // 120
        // 121
        // 122
        if (0u == map_has_this_key__48) {
          uint32_t new_index__52;
          int out_of_space__52 = !dchain_allocate_new_index(dchain, &new_index__52, now);

          // 120
          // 121
          if (false == ((out_of_space__52) & (0u == number_of_freed_flows__36))) {
            uint8_t* vector_value_out = 0u;
            vector_borrow(vector, new_index__52, (void**)(&vector_value_out));
            vector_value_out[0u] = tcpudp_header_1->src_port & 0xff;
            vector_value_out[1u] = (tcpudp_header_1->src_port >> 8) & 0xff;
            vector_value_out[2u] = tcpudp_header_1->dst_port & 0xff;
            vector_value_out[3u] = (tcpudp_header_1->dst_port >> 8) & 0xff;
            vector_value_out[4u] = ipv4_header_1->src_addr & 0xff;
            vector_value_out[5u] = (ipv4_header_1->src_addr >> 8) & 0xff;
            vector_value_out[6u] = (ipv4_header_1->src_addr >> 16) & 0xff;
            vector_value_out[7u] = (ipv4_header_1->src_addr >> 24) & 0xff;
            vector_value_out[8u] = ipv4_header_1->dst_addr & 0xff;
            vector_value_out[9u] = (ipv4_header_1->dst_addr >> 8) & 0xff;
            vector_value_out[10u] = (ipv4_header_1->dst_addr >> 16) & 0xff;
            vector_value_out[11u] = (ipv4_header_1->dst_addr >> 24) & 0xff;
            vector_value_out[12u] = ipv4_header_1->next_proto_id;
            vector_value_out[13u] = 171u;
            vector_value_out[14u] = 171u;
            vector_value_out[15u] = 171u;
            map_put(map, vector_value_out, new_index__52);
            vector_return(vector, new_index__52, vector_value_out);
            int overflow__58 = sketch_fetch(sketch);

            // 120
            if (0u == overflow__58) {
              int success__61 = sketch_touch_buckets(sketch, now);
              return 1;
            }

            // 121
            else {
              // dropping
              return device;
            } // !(0u == overflow__58)

          }

          // 122
          else {
            return 1;
          } // !(false == ((out_of_space__52) & (0u == number_of_freed_flows__36)))

        }

        // 123
        else {
          dchain_rejuvenate_index(dchain, map_value_out, now);
          sketch_refresh(sketch, now);
          return 1;
        } // !(0u == map_has_this_key__48)

      } // !device

    }

    // 124
    else {
      // dropping
      return device;
    } // !(0u == ((0u == ((6u == ipv4_header_1->next_proto_id) | (17u == ipv4_header_1->next_proto_id))) | ((4294967262u + packet_length) < 4ul)))

  }

  // 125
  else {
    // dropping
    return device;
  } // !(0u == ((8u != ether_header_1->ether_type) | ((4294967282u + packet_length) < 20ul)))

}
