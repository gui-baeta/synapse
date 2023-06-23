
bool FlowId_eq(void* a, void* b) ;
uint32_t FlowId_hash(void* obj) ;
void FlowId_allocate(void* obj) ;
struct Map* map;
struct Vector* vector;
struct DoubleChain* dchain;

bool nf_init() {
  int map_allocation_succeeded__1 = map_allocate(FlowId_eq, FlowId_hash, 65536u, &map);

  // 120
  // 121
  // 122
  if (map_allocation_succeeded__1) {
    int vector_alloc_success__4 = vector_allocate(16u, 65536u, FlowId_allocate, &vector);

    // 120
    // 121
    if (vector_alloc_success__4) {
      int is_dchain_allocated__7 = dchain_allocate(65536u, &dchain);

      // 120
      if (is_dchain_allocated__7) {
        return 1;
      }

      // 121
      else {
        return 0;
      } // !is_dchain_allocated__7

    }

    // 122
    else {
      return 0;
    } // !vector_alloc_success__4

  }

  // 123
  else {
    return 0;
  } // !map_allocation_succeeded__1

}

int nf_process(uint16_t device, uint8_t* packet, uint16_t packet_length, int64_t now) {
  int number_of_freed_flows__24 = expire_items_single_map(dchain, vector, map, now - 100000000000ul);
  struct rte_ether_hdr* ether_header_1 = (struct rte_ether_hdr*)(packet);

  // 125
  // 126
  // 127
  // 128
  // 129
  // 130
  // 131
  if (0u == ((8u != ether_header_1->ether_type) | ((4294967282u + packet_length) < 20ul))) {
    struct rte_ipv4_hdr* ipv4_header_1 = (struct rte_ipv4_hdr*)(packet + 14u);

    // 125
    // 126
    // 127
    // 128
    // 129
    // 130
    if (0u == ((0u == ((6u == ipv4_header_1->next_proto_id) | (17u == ipv4_header_1->next_proto_id))) | ((4294967262u + packet_length) < 4ul))) {
      struct tcpudp_hdr* tcpudp_header_1 = (struct tcpudp_hdr*)(packet + (14u + 20u));

      // 125
      // 126
      // 127
      if (device) {
        int32_t dchain_is_index_allocated__36 = dchain_is_index_allocated(dchain, tcpudp_header_1->dst_port);

        // 125
        // 126
        if (dchain_is_index_allocated__36) {
          uint8_t* vector_value_out = 0u;
          vector_borrow(vector, tcpudp_header_1->dst_port, (void**)(&vector_value_out));
          vector_return(vector, tcpudp_header_1->dst_port, vector_value_out);

          // 125
          if (0u == (((vector_value_out[8ul] != ipv4_header_1->src_addr) | (vector_value_out[2ul] != tcpudp_header_1->src_port)) | (vector_value_out[14ul] != ipv4_header_1->next_proto_id))) {
            int checksum__43 = rte_ipv4_udptcp_cksum(ipv4_header_1, tcpudp_header_1);
            tcpudp_header_1->dst_port = vector_value_out[0ul];
            ipv4_header_1->hdr_checksum = checksum__43 & 0xffff;
            ipv4_header_1->dst_addr = vector_value_out[4ul];
            ether_header_1->d_addr.addr_bytes[0ul] = 1u;
            ether_header_1->d_addr.addr_bytes[1ul] = 35u;
            ether_header_1->d_addr.addr_bytes[2ul] = 69u;
            ether_header_1->d_addr.addr_bytes[3ul] = 103u;
            ether_header_1->d_addr.addr_bytes[4ul] = 137u;
            ether_header_1->d_addr.addr_bytes[5ul] = 0u;
            ether_header_1->s_addr.addr_bytes[0ul] = 0u;
            ether_header_1->s_addr.addr_bytes[1ul] = 0u;
            ether_header_1->s_addr.addr_bytes[2ul] = 0u;
            ether_header_1->s_addr.addr_bytes[3ul] = 0u;
            ether_header_1->s_addr.addr_bytes[4ul] = 0u;
            ether_header_1->s_addr.addr_bytes[5ul] = 0u;
            return 0;
          }

          // 126
          else {
            // dropping
            return device;
          } // !(0u == (((vector_value_out[8ul] != ipv4_header_1->src_addr) | (vector_value_out[2ul] != tcpudp_header_1->src_port)) | (vector_value_out[14ul] != ipv4_header_1->next_proto_id)))

        }

        // 127
        else {
          // dropping
          return device;
        } // !dchain_is_index_allocated__36

      }

      // 128
      // 129
      // 130
      else {
        uint8_t map_key[15];
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
        map_key[12u] = device & 0xff;
        map_key[13u] = (device >> 8) & 0xff;
        map_key[14u] = ipv4_header_1->next_proto_id;
        int map_value_out;
        int map_has_this_key__68 = map_get(map, &map_key, &map_value_out);

        // 128
        // 129
        if (0u == map_has_this_key__68) {
          uint32_t new_index__71;
          int out_of_space__71 = !dchain_allocate_new_index(dchain, &new_index__71, now);

          // 128
          if (false == ((out_of_space__71) & (0u == number_of_freed_flows__24))) {
            uint8_t* vector_value_out = 0u;
            vector_borrow(vector, new_index__71, (void**)(&vector_value_out));
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
            vector_value_out[12u] = device & 0xff;
            vector_value_out[13u] = (device >> 8) & 0xff;
            vector_value_out[14u] = ipv4_header_1->next_proto_id;
            vector_value_out[15u] = 171u;
            map_put(map, vector_value_out, new_index__71);
            vector_return(vector, new_index__71, vector_value_out);
            int checksum__77 = rte_ipv4_udptcp_cksum(ipv4_header_1, tcpudp_header_1);
            tcpudp_header_1->src_port = new_index__71 & 0xffff;
            ipv4_header_1->hdr_checksum = checksum__77 & 0xffff;
            ipv4_header_1->src_addr = 0u;
            ether_header_1->d_addr.addr_bytes[0ul] = 1u;
            ether_header_1->d_addr.addr_bytes[1ul] = 35u;
            ether_header_1->d_addr.addr_bytes[2ul] = 69u;
            ether_header_1->d_addr.addr_bytes[3ul] = 103u;
            ether_header_1->d_addr.addr_bytes[4ul] = 137u;
            ether_header_1->d_addr.addr_bytes[5ul] = 1u;
            ether_header_1->s_addr.addr_bytes[0ul] = 0u;
            ether_header_1->s_addr.addr_bytes[1ul] = 0u;
            ether_header_1->s_addr.addr_bytes[2ul] = 0u;
            ether_header_1->s_addr.addr_bytes[3ul] = 0u;
            ether_header_1->s_addr.addr_bytes[4ul] = 0u;
            ether_header_1->s_addr.addr_bytes[5ul] = 0u;
            return 1;
          }

          // 129
          else {
            // dropping
            return device;
          } // !(false == ((out_of_space__71) & (0u == number_of_freed_flows__24)))

        }

        // 130
        else {
          dchain_rejuvenate_index(dchain, map_value_out, now);
          int checksum__95 = rte_ipv4_udptcp_cksum(ipv4_header_1, tcpudp_header_1);
          tcpudp_header_1->src_port = map_value_out & 0xffff;
          ipv4_header_1->hdr_checksum = checksum__95 & 0xffff;
          ipv4_header_1->src_addr = 0u;
          ether_header_1->d_addr.addr_bytes[0ul] = 1u;
          ether_header_1->d_addr.addr_bytes[1ul] = 35u;
          ether_header_1->d_addr.addr_bytes[2ul] = 69u;
          ether_header_1->d_addr.addr_bytes[3ul] = 103u;
          ether_header_1->d_addr.addr_bytes[4ul] = 137u;
          ether_header_1->d_addr.addr_bytes[5ul] = 1u;
          ether_header_1->s_addr.addr_bytes[0ul] = 0u;
          ether_header_1->s_addr.addr_bytes[1ul] = 0u;
          ether_header_1->s_addr.addr_bytes[2ul] = 0u;
          ether_header_1->s_addr.addr_bytes[3ul] = 0u;
          ether_header_1->s_addr.addr_bytes[4ul] = 0u;
          ether_header_1->s_addr.addr_bytes[5ul] = 0u;
          return 1;
        } // !(0u == map_has_this_key__68)

      } // !device

    }

    // 131
    else {
      // dropping
      return device;
    } // !(0u == ((0u == ((6u == ipv4_header_1->next_proto_id) | (17u == ipv4_header_1->next_proto_id))) | ((4294967262u + packet_length) < 4ul)))

  }

  // 132
  else {
    // dropping
    return device;
  } // !(0u == ((8u != ether_header_1->ether_type) | ((4294967282u + packet_length) < 20ul)))

}
