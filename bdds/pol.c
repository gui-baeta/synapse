
bool ip_addr_eq(void* a, void* b) ;
uint32_t ip_addr_hash(void* obj) ;
void ip_addr_allocate(void* obj) ;
void DynamicValue_allocate(void* obj) ;
struct Map* map;
struct Vector* vector;
struct DoubleChain* dchain;
struct Vector* vector_1;

bool nf_init() {
  int map_allocation_succeeded__1 = map_allocate(ip_addr_eq, ip_addr_hash, 65536u, &map);

  // 117
  // 118
  // 119
  // 120
  if (map_allocation_succeeded__1) {
    int vector_alloc_success__4 = vector_allocate(4u, 65536u, ip_addr_allocate, &vector);

    // 117
    // 118
    // 119
    if (vector_alloc_success__4) {
      int is_dchain_allocated__7 = dchain_allocate(65536u, &dchain);

      // 117
      // 118
      if (is_dchain_allocated__7) {
        int vector_alloc_success__10 = vector_allocate(16u, 65536u, DynamicValue_allocate, &vector_1);

        // 117
        if (vector_alloc_success__10) {
          return 1;
        }

        // 118
        else {
          return 0;
        } // !vector_alloc_success__10

      }

      // 119
      else {
        return 0;
      } // !is_dchain_allocated__7

    }

    // 120
    else {
      return 0;
    } // !vector_alloc_success__4

  }

  // 121
  else {
    return 0;
  } // !map_allocation_succeeded__1

}

int nf_process(uint16_t device, uint8_t* packet, uint16_t packet_length, int64_t now) {
  struct rte_ether_hdr* ether_header_1 = (struct rte_ether_hdr*)(packet);

  // 123
  // 124
  // 125
  // 126
  // 127
  // 128
  // 129
  if (0u == ((8u != ether_header_1->ether_type) | ((4294967282u + packet_length) < 20ul))) {
    struct rte_ipv4_hdr* ipv4_header_1 = (struct rte_ipv4_hdr*)(packet + 14u);
    int number_of_freed_flows__32 = expire_items_single_map(dchain, vector, map, now - 10000000000ul);

    // 123
    if (device) {
      return 0;
    }

    // 124
    // 125
    // 126
    // 127
    // 128
    // 129
    else {
      uint8_t map_key[4];
      map_key[0u] = ipv4_header_1->dst_addr & 0xff;
      map_key[1u] = (ipv4_header_1->dst_addr >> 8) & 0xff;
      map_key[2u] = (ipv4_header_1->dst_addr >> 16) & 0xff;
      map_key[3u] = (ipv4_header_1->dst_addr >> 24) & 0xff;
      int map_value_out;
      int map_has_this_key__42 = map_get(map, &map_key, &map_value_out);

      // 124
      // 125
      if (0u == map_has_this_key__42) {
        uint32_t new_index__45;
        int out_of_space__45 = !dchain_allocate_new_index(dchain, &new_index__45, now);

        // 124
        if (false == ((out_of_space__45) & (0u == number_of_freed_flows__32))) {
          uint8_t* vector_value_out = 0u;
          vector_borrow(vector, new_index__45, (void**)(&vector_value_out));
          vector_value_out[0u] = ipv4_header_1->dst_addr & 0xff;
          vector_value_out[1u] = (ipv4_header_1->dst_addr >> 8) & 0xff;
          vector_value_out[2u] = (ipv4_header_1->dst_addr >> 16) & 0xff;
          vector_value_out[3u] = (ipv4_header_1->dst_addr >> 24) & 0xff;
          uint8_t* vector_value_out_1 = 0u;
          vector_borrow(vector_1, new_index__45, (void**)(&vector_value_out_1));
          vector_value_out_1[0u] = 10000000000ul - packet_length;
          vector_value_out_1[1u] = ((10000000000ul - packet_length) >> 8ul) & 0xff;
          vector_value_out_1[2u] = ((10000000000ul - packet_length) >> 16ul) & 0xff;
          vector_value_out_1[3u] = 84u;
          vector_value_out_1[4u] = 2u;
          vector_value_out_1[5u] = 0u;
          vector_value_out_1[6u] = 0u;
          vector_value_out_1[7u] = 0u;
          vector_value_out_1[8u] = now & 0xff;
          vector_value_out_1[9u] = (now >> 8) & 0xff;
          vector_value_out_1[10u] = (now >> 16) & 0xff;
          vector_value_out_1[11u] = (now >> 24) & 0xff;
          vector_value_out_1[12u] = (now >> 32) & 0xff;
          vector_value_out_1[13u] = (now >> 40) & 0xff;
          vector_value_out_1[14u] = (now >> 48) & 0xff;
          vector_value_out_1[15u] = (now >> 56) & 0xff;
          map_put(map, vector_value_out, new_index__45);
          vector_return(vector, new_index__45, vector_value_out);
          vector_return(vector_1, new_index__45, vector_value_out_1);
          return 1;
        }

        // 125
        else {
          // dropping
          return device;
        } // !(false == ((out_of_space__45) & (0u == number_of_freed_flows__32)))

      }

      // 126
      // 127
      // 128
      // 129
      else {
        dchain_rejuvenate_index(dchain, map_value_out, now);
        uint8_t* vector_value_out = 0u;
        vector_borrow(vector_1, map_value_out, (void**)(&vector_value_out));
        vector_value_out[0u] = 10000000000ul - packet_length;
        vector_value_out[1u] = ((10000000000ul - packet_length) >> 8ul) & 0xff;
        vector_value_out[2u] = ((10000000000ul - packet_length) >> 16ul) & 0xff;
        vector_value_out[3u] = 84u;
        vector_value_out[4u] = 2u;
        vector_value_out[5u] = 0u;
        vector_value_out[6u] = 0u;
        vector_value_out[7u] = 0u;
        vector_value_out[8u] = now & 0xff;
        vector_value_out[9u] = (now >> 8) & 0xff;
        vector_value_out[10u] = (now >> 16) & 0xff;
        vector_value_out[11u] = (now >> 24) & 0xff;
        vector_value_out[12u] = (now >> 32) & 0xff;
        vector_value_out[13u] = (now >> 40) & 0xff;
        vector_value_out[14u] = (now >> 48) & 0xff;
        vector_value_out[15u] = (now >> 56) & 0xff;

        // 126
        // 127
        // 128
        if ((now - vector_value_out[8ul]) < 10000000000ul) {

          // 126
          // 127
          if (false == (10000000000ul < (vector_value_out[0ul] + ((1000000000ul * (now - vector_value_out[8ul])) / 1000000000ul)))) {

            // 126
            if (false == (packet_length < (vector_value_out[0ul] + ((1000000000ul * (now - vector_value_out[8ul])) / 1000000000ul)))) {
              vector_return(vector_1, map_value_out, vector_value_out);
              // dropping
              return device;
            }

            // 127
            else {
              vector_return(vector_1, map_value_out, vector_value_out);
              return 1;
            } // !(false == (packet_length < (vector_value_out[0ul] + ((1000000000ul * (now - vector_value_out[8ul])) / 1000000000ul))))

          }

          // 128
          else {
            vector_return(vector_1, map_value_out, vector_value_out);
            return 1;
          } // !(false == (10000000000ul < (vector_value_out[0ul] + ((1000000000ul * (now - vector_value_out[8ul])) / 1000000000ul))))

        }

        // 129
        else {
          vector_return(vector_1, map_value_out, vector_value_out);
          return 1;
        } // !((now - vector_value_out[8ul]) < 10000000000ul)

      } // !(0u == map_has_this_key__42)

    } // !device

  }

  // 130
  else {
    // dropping
    return device;
  } // !(0u == ((8u != ether_header_1->ether_type) | ((4294967282u + packet_length) < 20ul)))

}
