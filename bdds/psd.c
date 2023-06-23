
bool ip_addr_eq(void* a, void* b) ;
uint32_t ip_addr_hash(void* obj) ;
void ip_addr_allocate(void* obj) ;
void counter_allocate(void* obj) ;
bool touched_port_eq(void* a, void* b) ;
uint32_t touched_port_hash(void* obj) ;
void touched_port_allocate(void* obj) ;
struct Map* map;
struct Vector* vector;
struct Vector* vector_1;
struct DoubleChain* dchain;
struct Map* map_1;
struct Vector* vector_2;

bool nf_init() {
  int map_allocation_succeeded__1 = map_allocate(ip_addr_eq, ip_addr_hash, 65536u, &map);

  // 140
  // 141
  // 142
  // 143
  // 144
  // 145
  if (map_allocation_succeeded__1) {
    int vector_alloc_success__4 = vector_allocate(4u, 65536u, ip_addr_allocate, &vector);

    // 140
    // 141
    // 142
    // 143
    // 144
    if (vector_alloc_success__4) {
      int vector_alloc_success__7 = vector_allocate(4u, 65536u, counter_allocate, &vector_1);

      // 140
      // 141
      // 142
      // 143
      if (vector_alloc_success__7) {
        int is_dchain_allocated__10 = dchain_allocate(65536u, &dchain);

        // 140
        // 141
        // 142
        if (is_dchain_allocated__10) {
          int map_allocation_succeeded__13 = map_allocate(touched_port_eq, touched_port_hash, 4194304u, &map_1);

          // 140
          // 141
          if (map_allocation_succeeded__13) {
            int vector_alloc_success__16 = vector_allocate(8u, 4194304u, touched_port_allocate, &vector_2);

            // 140
            if (vector_alloc_success__16) {
              return 1;
            }

            // 141
            else {
              return 0;
            } // !vector_alloc_success__16

          }

          // 142
          else {
            return 0;
          } // !map_allocation_succeeded__13

        }

        // 143
        else {
          return 0;
        } // !is_dchain_allocated__10

      }

      // 144
      else {
        return 0;
      } // !vector_alloc_success__7

    }

    // 145
    else {
      return 0;
    } // !vector_alloc_success__4

  }

  // 146
  else {
    return 0;
  } // !map_allocation_succeeded__1

}

int nf_process(uint16_t device, uint8_t* packet, uint16_t packet_length, int64_t now) {
  struct rte_ether_hdr* ether_header_1 = (struct rte_ether_hdr*)(packet);

  // 148
  // 149
  // 150
  // 151
  // 152
  // 153
  // 154
  if (0u == ((8u != ether_header_1->ether_type) | ((4294967282u + packet_length) < 20ul))) {
    struct rte_ipv4_hdr* ipv4_header_1 = (struct rte_ipv4_hdr*)(packet + 14u);

    // 148
    // 149
    // 150
    // 151
    // 152
    // 153
    if (0u == ((0u == ((6u == ipv4_header_1->next_proto_id) | (17u == ipv4_header_1->next_proto_id))) | ((4294967262u + packet_length) < 4ul))) {
      struct tcpudp_hdr* tcpudp_header_1 = (struct tcpudp_hdr*)(packet + (14u + 20u));
      int number_of_freed_flows__42 = expire_items_single_map(dchain, vector, map, now - 10000000000ul);

      // 148
      if (device) {
        return 0;
      }

      // 149
      // 150
      // 151
      // 152
      // 153
      else {
        uint8_t map_key[4];
        map_key[0u] = ipv4_header_1->src_addr & 0xff;
        map_key[1u] = (ipv4_header_1->src_addr >> 8) & 0xff;
        map_key[2u] = (ipv4_header_1->src_addr >> 16) & 0xff;
        map_key[3u] = (ipv4_header_1->src_addr >> 24) & 0xff;
        int map_value_out;
        int map_has_this_key__53 = map_get(map, &map_key, &map_value_out);

        // 149
        // 150
        if (0u == map_has_this_key__53) {
          uint32_t new_index__56;
          int out_of_space__56 = !dchain_allocate_new_index(dchain, &new_index__56, now);

          // 149
          if (false == ((out_of_space__56) & (0u == number_of_freed_flows__42))) {
            uint8_t* vector_value_out = 0u;
            vector_borrow(vector, new_index__56, (void**)(&vector_value_out));
            vector_value_out[0u] = ipv4_header_1->src_addr & 0xff;
            vector_value_out[1u] = (ipv4_header_1->src_addr >> 8) & 0xff;
            vector_value_out[2u] = (ipv4_header_1->src_addr >> 16) & 0xff;
            vector_value_out[3u] = (ipv4_header_1->src_addr >> 24) & 0xff;
            uint8_t* vector_value_out_1 = 0u;
            vector_borrow(vector_1, new_index__56, (void**)(&vector_value_out_1));
            vector_value_out_1[0u] = 1u;
            vector_value_out_1[1u] = 0u;
            vector_value_out_1[2u] = 0u;
            vector_value_out_1[3u] = 0u;
            int number_of_freed_flows__61 = expire_items_single_map_iteratively(vector_2, map_1, new_index__56, ((int*)(vector_value_out_1))[0]);
            uint8_t* vector_value_out_2 = 0u;
            vector_borrow(vector_2, 64u * new_index__56, (void**)(&vector_value_out_2));
            vector_value_out_2[0u] = ipv4_header_1->src_addr & 0xff;
            vector_value_out_2[1u] = (ipv4_header_1->src_addr >> 8) & 0xff;
            vector_value_out_2[2u] = (ipv4_header_1->src_addr >> 16) & 0xff;
            vector_value_out_2[3u] = (ipv4_header_1->src_addr >> 24) & 0xff;
            vector_value_out_2[4u] = tcpudp_header_1->dst_port & 0xff;
            vector_value_out_2[5u] = (tcpudp_header_1->dst_port >> 8) & 0xff;
            vector_value_out_2[6u] = vector_value_out_2[6ul];
            vector_value_out_2[7u] = vector_value_out_2[7ul];
            map_put(map, vector_value_out, new_index__56);
            map_put(map_1, vector_value_out_2, 0u);
            vector_return(vector, new_index__56, vector_value_out);
            vector_return(vector_1, new_index__56, vector_value_out_1);
            vector_return(vector_2, 64u * new_index__56, vector_value_out_2);
            return 1;
          }

          // 150
          else {
            return 1;
          } // !(false == ((out_of_space__56) & (0u == number_of_freed_flows__42)))

        }

        // 151
        // 152
        // 153
        else {
          dchain_rejuvenate_index(dchain, map_value_out, now);
          uint8_t* vector_value_out = 0u;
          vector_borrow(vector_1, map_value_out, (void**)(&vector_value_out));
          uint8_t map_key_1[6];
          map_key_1[0u] = ipv4_header_1->src_addr & 0xff;
          map_key_1[1u] = (ipv4_header_1->src_addr >> 8) & 0xff;
          map_key_1[2u] = (ipv4_header_1->src_addr >> 16) & 0xff;
          map_key_1[3u] = (ipv4_header_1->src_addr >> 24) & 0xff;
          map_key_1[4u] = tcpudp_header_1->dst_port & 0xff;
          map_key_1[5u] = (tcpudp_header_1->dst_port >> 8) & 0xff;
          int map_value_out_1;
          int map_has_this_key__86 = map_get(map_1, &map_key_1, &map_value_out_1);

          // 151
          // 152
          if (0u == map_has_this_key__86) {

            // 151
            if (false == (64u <= ((uint32_t*)(vector_value_out))[0])) {
              uint8_t* vector_value_out_1 = 0u;
              vector_borrow(vector_2, (64u * map_value_out) + ((int*)(vector_value_out))[0], (void**)(&vector_value_out_1));
              vector_value_out_1[0u] = ipv4_header_1->src_addr & 0xff;
              vector_value_out_1[1u] = (ipv4_header_1->src_addr >> 8) & 0xff;
              vector_value_out_1[2u] = (ipv4_header_1->src_addr >> 16) & 0xff;
              vector_value_out_1[3u] = (ipv4_header_1->src_addr >> 24) & 0xff;
              vector_value_out_1[4u] = tcpudp_header_1->dst_port & 0xff;
              vector_value_out_1[5u] = (tcpudp_header_1->dst_port >> 8) & 0xff;
              vector_value_out_1[6u] = vector_value_out_1[6ul];
              vector_value_out_1[7u] = vector_value_out_1[7ul];
              map_put(map_1, vector_value_out_1, ((int*)(vector_value_out))[0]);
              vector_return(vector_2, (64u * map_value_out) + ((int*)(vector_value_out))[0], vector_value_out_1);
              vector_return(vector_1, map_value_out, vector_value_out);
              return 1;
            }

            // 152
            else {
              vector_return(vector_1, map_value_out, vector_value_out);
              // dropping
              return device;
            } // !(false == (64u <= ((uint32_t*)(vector_value_out))[0]))

          }

          // 153
          else {
            vector_return(vector_1, map_value_out, vector_value_out);
            return 1;
          } // !(0u == map_has_this_key__86)

        } // !(0u == map_has_this_key__53)

      } // !device

    }

    // 154
    else {
      // dropping
      return device;
    } // !(0u == ((0u == ((6u == ipv4_header_1->next_proto_id) | (17u == ipv4_header_1->next_proto_id))) | ((4294967262u + packet_length) < 4ul)))

  }

  // 155
  else {
    // dropping
    return device;
  } // !(0u == ((8u != ether_header_1->ether_type) | ((4294967282u + packet_length) < 20ul)))

}
