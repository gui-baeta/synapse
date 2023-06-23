
bool LoadBalancedFlow_eq(void* a, void* b) ;
uint32_t LoadBalancedFlow_hash(void* obj) ;
void LoadBalancedFlow_allocate(void* obj) ;
void null_init(void* obj) ;
bool ip_addr_eq(void* a, void* b) ;
uint32_t ip_addr_hash(void* obj) ;
void ip_addr_allocate(void* obj) ;
void LoadBalancedBackend_allocate(void* obj) ;
struct Map* map;
struct Vector* vector;
struct DoubleChain* dchain;
struct Vector* vector_1;
struct Map* map_1;
struct Vector* vector_2;
struct Vector* vector_3;
struct DoubleChain* dchain_1;
struct Vector* vector_4;

bool nf_init() {
  int map_allocation_succeeded__1 = map_allocate(LoadBalancedFlow_eq, LoadBalancedFlow_hash, 65536u, &map);

  // 279
  // 280
  // 281
  // 282
  // 283
  // 284
  // 285
  // 286
  // 287
  // 288
  if (map_allocation_succeeded__1) {
    int vector_alloc_success__4 = vector_allocate(16u, 65536u, LoadBalancedFlow_allocate, &vector);

    // 279
    // 280
    // 281
    // 282
    // 283
    // 284
    // 285
    // 286
    // 287
    if (vector_alloc_success__4) {
      int is_dchain_allocated__7 = dchain_allocate(65536u, &dchain);

      // 279
      // 280
      // 281
      // 282
      // 283
      // 284
      // 285
      // 286
      if (is_dchain_allocated__7) {
        int vector_alloc_success__10 = vector_allocate(4u, 65536u, null_init, &vector_1);

        // 279
        // 280
        // 281
        // 282
        // 283
        // 284
        // 285
        if (vector_alloc_success__10) {
          int map_allocation_succeeded__13 = map_allocate(ip_addr_eq, ip_addr_hash, 32u, &map_1);

          // 279
          // 280
          // 281
          // 282
          // 283
          // 284
          if (map_allocation_succeeded__13) {
            int vector_alloc_success__16 = vector_allocate(4u, 32u, ip_addr_allocate, &vector_2);

            // 279
            // 280
            // 281
            // 282
            // 283
            if (vector_alloc_success__16) {
              int vector_alloc_success__19 = vector_allocate(12u, 32u, LoadBalancedBackend_allocate, &vector_3);

              // 279
              // 280
              // 281
              // 282
              if (vector_alloc_success__19) {
                int is_dchain_allocated__22 = dchain_allocate(32u, &dchain_1);

                // 279
                // 280
                // 281
                if (is_dchain_allocated__22) {
                  int vector_alloc_success__25 = vector_allocate(4u, 3104u, null_init, &vector_4);

                  // 279
                  // 280
                  if (vector_alloc_success__25) {
                    int cht_fill_cht_successful__28 = cht_fill_cht(vector_4, 97u, 32u);

                    // 279
                    if (cht_fill_cht_successful__28) {
                      return 1;
                    }

                    // 280
                    else {
                      return 0;
                    } // !cht_fill_cht_successful__28

                  }

                  // 281
                  else {
                    return 0;
                  } // !vector_alloc_success__25

                }

                // 282
                else {
                  return 0;
                } // !is_dchain_allocated__22

              }

              // 283
              else {
                return 0;
              } // !vector_alloc_success__19

            }

            // 284
            else {
              return 0;
            } // !vector_alloc_success__16

          }

          // 285
          else {
            return 0;
          } // !map_allocation_succeeded__13

        }

        // 286
        else {
          return 0;
        } // !vector_alloc_success__10

      }

      // 287
      else {
        return 0;
      } // !is_dchain_allocated__7

    }

    // 288
    else {
      return 0;
    } // !vector_alloc_success__4

  }

  // 289
  else {
    return 0;
  } // !map_allocation_succeeded__1

}

int nf_process(uint16_t device, uint8_t* packet, uint16_t packet_length, int64_t now) {
  int number_of_freed_flows__45 = expire_items_single_map(dchain, vector, map, now - 100000000000ul);
  int number_of_freed_flows__46 = expire_items_single_map(dchain_1, vector_2, map_1, now - 100000000000ul);
  struct rte_ether_hdr* ether_header_1 = (struct rte_ether_hdr*)(packet);

  // 291
  // 292
  // 293
  // 294
  // 295
  // 296
  // 297
  // 298
  // 299
  // 300
  // 301
  // 302
  // 303
  // 304
  // 305
  // 306
  // 307
  if (0u == ((8u != ether_header_1->ether_type) | ((4294967282u + packet_length) < 20ul))) {
    struct rte_ipv4_hdr* ipv4_header_1 = (struct rte_ipv4_hdr*)(packet + 14u);

    // 291
    // 292
    // 293
    // 294
    // 295
    // 296
    // 297
    // 298
    // 299
    // 300
    // 301
    // 302
    // 303
    // 304
    // 305
    // 306
    if (0u == ((0u == ((6u == ipv4_header_1->next_proto_id) | (17u == ipv4_header_1->next_proto_id))) | ((4294967262u + packet_length) < 4ul))) {
      struct tcpudp_hdr* tcpudp_header_1 = (struct tcpudp_hdr*)(packet + (14u + 20u));

      // 291
      // 292
      // 293
      // 294
      // 295
      // 296
      // 297
      // 298
      // 299
      // 300
      // 301
      // 302
      // 303
      if (device) {

        // 291
        // 292
        // 293
        // 294
        // 295
        // 296
        // 297
        // 298
        // 299
        // 300
        if (1u != device) {
          uint8_t map_key[13];
          map_key[0u] = ipv4_header_1->src_addr & 0xff;
          map_key[1u] = (ipv4_header_1->src_addr >> 8) & 0xff;
          map_key[2u] = (ipv4_header_1->src_addr >> 16) & 0xff;
          map_key[3u] = (ipv4_header_1->src_addr >> 24) & 0xff;
          map_key[4u] = ipv4_header_1->dst_addr & 0xff;
          map_key[5u] = (ipv4_header_1->dst_addr >> 8) & 0xff;
          map_key[6u] = (ipv4_header_1->dst_addr >> 16) & 0xff;
          map_key[7u] = (ipv4_header_1->dst_addr >> 24) & 0xff;
          map_key[8u] = tcpudp_header_1->src_port & 0xff;
          map_key[9u] = (tcpudp_header_1->src_port >> 8) & 0xff;
          map_key[10u] = tcpudp_header_1->dst_port & 0xff;
          map_key[11u] = (tcpudp_header_1->dst_port >> 8) & 0xff;
          map_key[12u] = ipv4_header_1->next_proto_id;
          int map_value_out;
          int map_has_this_key__60 = map_get(map, &map_key, &map_value_out);

          // 291
          // 292
          // 293
          // 294
          // 295
          if (0u == map_has_this_key__60) {
            uint8_t hashed_obj[16];
            hashed_obj[0u] = ipv4_header_1->src_addr & 0xff;
            hashed_obj[1u] = (ipv4_header_1->src_addr >> 8) & 0xff;
            hashed_obj[2u] = (ipv4_header_1->src_addr >> 16) & 0xff;
            hashed_obj[3u] = (ipv4_header_1->src_addr >> 24) & 0xff;
            hashed_obj[4u] = ipv4_header_1->dst_addr & 0xff;
            hashed_obj[5u] = (ipv4_header_1->dst_addr >> 8) & 0xff;
            hashed_obj[6u] = (ipv4_header_1->dst_addr >> 16) & 0xff;
            hashed_obj[7u] = (ipv4_header_1->dst_addr >> 24) & 0xff;
            hashed_obj[8u] = tcpudp_header_1->src_port & 0xff;
            hashed_obj[9u] = (tcpudp_header_1->src_port >> 8) & 0xff;
            hashed_obj[10u] = tcpudp_header_1->dst_port & 0xff;
            hashed_obj[11u] = (tcpudp_header_1->dst_port >> 8) & 0xff;
            hashed_obj[12u] = ipv4_header_1->next_proto_id;
            hashed_obj[13u] = 171u;
            hashed_obj[14u] = 171u;
            hashed_obj[15u] = 171u;
            uint32_t LoadBalancedFlow_hash__63 = LoadBalancedFlow_hash(hashed_obj);
            uint32_t chosen_backend__64 = 0u;
            int32_t prefered_backend_found__64 = cht_find_preferred_available_backend(LoadBalancedFlow_hash__63, vector_4, dchain_1, 97u, 32u, &chosen_backend__64);

            // 291
            if (0u == prefered_backend_found__64) {
              // dropping
              return device;
            }

            // 292
            // 293
            // 294
            // 295
            else {
              uint32_t new_index__75;
              int out_of_space__75 = !dchain_allocate_new_index(dchain, &new_index__75, now);

              // 292
              // 293
              if (false == ((out_of_space__75) & (0u == number_of_freed_flows__45))) {
                uint8_t* vector_value_out = 0u;
                vector_borrow(vector, new_index__75, (void**)(&vector_value_out));
                vector_value_out[0u] = ipv4_header_1->src_addr & 0xff;
                vector_value_out[1u] = (ipv4_header_1->src_addr >> 8) & 0xff;
                vector_value_out[2u] = (ipv4_header_1->src_addr >> 16) & 0xff;
                vector_value_out[3u] = (ipv4_header_1->src_addr >> 24) & 0xff;
                vector_value_out[4u] = ipv4_header_1->dst_addr & 0xff;
                vector_value_out[5u] = (ipv4_header_1->dst_addr >> 8) & 0xff;
                vector_value_out[6u] = (ipv4_header_1->dst_addr >> 16) & 0xff;
                vector_value_out[7u] = (ipv4_header_1->dst_addr >> 24) & 0xff;
                vector_value_out[8u] = tcpudp_header_1->src_port & 0xff;
                vector_value_out[9u] = (tcpudp_header_1->src_port >> 8) & 0xff;
                vector_value_out[10u] = tcpudp_header_1->dst_port & 0xff;
                vector_value_out[11u] = (tcpudp_header_1->dst_port >> 8) & 0xff;
                vector_value_out[12u] = ipv4_header_1->next_proto_id;
                vector_value_out[13u] = 171u;
                vector_value_out[14u] = 171u;
                vector_value_out[15u] = 171u;
                uint8_t* vector_value_out_1 = 0u;
                vector_borrow(vector_1, new_index__75, (void**)(&vector_value_out_1));
                vector_value_out_1[0u] = chosen_backend__64 & 0xff;
                vector_value_out_1[1u] = (chosen_backend__64 >> 8) & 0xff;
                vector_value_out_1[2u] = (chosen_backend__64 >> 16) & 0xff;
                vector_value_out_1[3u] = (chosen_backend__64 >> 24) & 0xff;
                vector_return(vector_1, new_index__75, vector_value_out_1);
                map_put(map, vector_value_out, new_index__75);
                vector_return(vector, new_index__75, vector_value_out);
                uint8_t* vector_value_out_2 = 0u;
                vector_borrow(vector_3, chosen_backend__64, (void**)(&vector_value_out_2));
                vector_return(vector_3, chosen_backend__64, vector_value_out_2);
                int checksum__85 = rte_ipv4_udptcp_cksum(ipv4_header_1, tcpudp_header_1);
                ipv4_header_1->hdr_checksum = checksum__85 & 0xffff;
                ipv4_header_1->dst_addr = vector_value_out_2[8ul];
                ether_header_1->d_addr.addr_bytes[0ul] = vector_value_out_2[2ul];
                ether_header_1->d_addr.addr_bytes[1ul] = vector_value_out_2[3ul];
                ether_header_1->d_addr.addr_bytes[2ul] = vector_value_out_2[4ul];
                ether_header_1->d_addr.addr_bytes[3ul] = vector_value_out_2[5ul];
                ether_header_1->d_addr.addr_bytes[4ul] = vector_value_out_2[6ul];
                ether_header_1->d_addr.addr_bytes[5ul] = vector_value_out_2[7ul];
                ether_header_1->s_addr.addr_bytes[0ul] = 171u;
                ether_header_1->s_addr.addr_bytes[1ul] = 171u;
                ether_header_1->s_addr.addr_bytes[2ul] = 171u;
                ether_header_1->s_addr.addr_bytes[3ul] = 171u;
                ether_header_1->s_addr.addr_bytes[4ul] = 171u;
                ether_header_1->s_addr.addr_bytes[5ul] = 171u;

                // 292
                if (vector_value_out_2[0ul]) {
                  return 1;
                }

                // 293
                else {
                  return 0;
                } // !vector_value_out_2[0ul]

              }

              // 294
              // 295
              else {
                uint8_t* vector_value_out = 0u;
                vector_borrow(vector_3, chosen_backend__64, (void**)(&vector_value_out));
                vector_return(vector_3, chosen_backend__64, vector_value_out);
                int checksum__103 = rte_ipv4_udptcp_cksum(ipv4_header_1, tcpudp_header_1);
                ipv4_header_1->hdr_checksum = checksum__103 & 0xffff;
                ipv4_header_1->dst_addr = vector_value_out[8ul];
                ether_header_1->d_addr.addr_bytes[0ul] = vector_value_out[2ul];
                ether_header_1->d_addr.addr_bytes[1ul] = vector_value_out[3ul];
                ether_header_1->d_addr.addr_bytes[2ul] = vector_value_out[4ul];
                ether_header_1->d_addr.addr_bytes[3ul] = vector_value_out[5ul];
                ether_header_1->d_addr.addr_bytes[4ul] = vector_value_out[6ul];
                ether_header_1->d_addr.addr_bytes[5ul] = vector_value_out[7ul];
                ether_header_1->s_addr.addr_bytes[0ul] = 171u;
                ether_header_1->s_addr.addr_bytes[1ul] = 171u;
                ether_header_1->s_addr.addr_bytes[2ul] = 171u;
                ether_header_1->s_addr.addr_bytes[3ul] = 171u;
                ether_header_1->s_addr.addr_bytes[4ul] = 171u;
                ether_header_1->s_addr.addr_bytes[5ul] = 171u;

                // 294
                if (vector_value_out[0ul]) {
                  return 1;
                }

                // 295
                else {
                  return 0;
                } // !vector_value_out[0ul]

              } // !(false == ((out_of_space__75) & (0u == number_of_freed_flows__45)))

            } // !(0u == prefered_backend_found__64)

          }

          // 296
          // 297
          // 298
          // 299
          // 300
          else {
            uint8_t* vector_value_out = 0u;
            vector_borrow(vector_1, map_value_out, (void**)(&vector_value_out));
            vector_return(vector_1, map_value_out, vector_value_out);
            int32_t dchain_is_index_allocated__121 = dchain_is_index_allocated(dchain_1, ((int*)(vector_value_out))[0u]);

            // 296
            // 297
            if (dchain_is_index_allocated__121) {
              dchain_rejuvenate_index(dchain, map_value_out, now);
              uint8_t* vector_value_out_1 = 0u;
              vector_borrow(vector_3, ((int*)(vector_value_out))[0], (void**)(&vector_value_out_1));
              vector_return(vector_3, ((int*)(vector_value_out))[0], vector_value_out_1);
              int checksum__127 = rte_ipv4_udptcp_cksum(ipv4_header_1, tcpudp_header_1);
              ipv4_header_1->hdr_checksum = checksum__127 & 0xffff;
              ipv4_header_1->dst_addr = vector_value_out_1[8ul];
              ether_header_1->d_addr.addr_bytes[0ul] = vector_value_out_1[2ul];
              ether_header_1->d_addr.addr_bytes[1ul] = vector_value_out_1[3ul];
              ether_header_1->d_addr.addr_bytes[2ul] = vector_value_out_1[4ul];
              ether_header_1->d_addr.addr_bytes[3ul] = vector_value_out_1[5ul];
              ether_header_1->d_addr.addr_bytes[4ul] = vector_value_out_1[6ul];
              ether_header_1->d_addr.addr_bytes[5ul] = vector_value_out_1[7ul];
              ether_header_1->s_addr.addr_bytes[0ul] = 171u;
              ether_header_1->s_addr.addr_bytes[1ul] = 171u;
              ether_header_1->s_addr.addr_bytes[2ul] = 171u;
              ether_header_1->s_addr.addr_bytes[3ul] = 171u;
              ether_header_1->s_addr.addr_bytes[4ul] = 171u;
              ether_header_1->s_addr.addr_bytes[5ul] = 171u;

              // 296
              if (vector_value_out_1[0ul]) {
                return 1;
              }

              // 297
              else {
                return 0;
              } // !vector_value_out_1[0ul]

            }

            // 298
            // 299
            // 300
            else {
              uint8_t* vector_value_out_1 = 0u;
              vector_borrow(vector, map_value_out, (void**)(&vector_value_out_1));
              uint8_t map_key_1[13];
              map_key_1[0u] = ipv4_header_1->src_addr & 0xff;
              map_key_1[1u] = (ipv4_header_1->src_addr >> 8) & 0xff;
              map_key_1[2u] = (ipv4_header_1->src_addr >> 16) & 0xff;
              map_key_1[3u] = (ipv4_header_1->src_addr >> 24) & 0xff;
              map_key_1[4u] = ipv4_header_1->dst_addr & 0xff;
              map_key_1[5u] = (ipv4_header_1->dst_addr >> 8) & 0xff;
              map_key_1[6u] = (ipv4_header_1->dst_addr >> 16) & 0xff;
              map_key_1[7u] = (ipv4_header_1->dst_addr >> 24) & 0xff;
              map_key_1[8u] = tcpudp_header_1->src_port & 0xff;
              map_key_1[9u] = (tcpudp_header_1->src_port >> 8) & 0xff;
              map_key_1[10u] = tcpudp_header_1->dst_port & 0xff;
              map_key_1[11u] = (tcpudp_header_1->dst_port >> 8) & 0xff;
              map_key_1[12u] = ipv4_header_1->next_proto_id;
              uint8_t trash[13];
              map_erase(map, &map_key_1, (void**)(&trash));
              dchain_free_index(dchain, map_value_out);
              vector_return(vector, map_value_out, vector_value_out_1);
              uint8_t map_key_2[13];
              map_key_2[0u] = ipv4_header_1->src_addr & 0xff;
              map_key_2[1u] = (ipv4_header_1->src_addr >> 8) & 0xff;
              map_key_2[2u] = (ipv4_header_1->src_addr >> 16) & 0xff;
              map_key_2[3u] = (ipv4_header_1->src_addr >> 24) & 0xff;
              map_key_2[4u] = ipv4_header_1->dst_addr & 0xff;
              map_key_2[5u] = (ipv4_header_1->dst_addr >> 8) & 0xff;
              map_key_2[6u] = (ipv4_header_1->dst_addr >> 16) & 0xff;
              map_key_2[7u] = (ipv4_header_1->dst_addr >> 24) & 0xff;
              map_key_2[8u] = tcpudp_header_1->src_port & 0xff;
              map_key_2[9u] = (tcpudp_header_1->src_port >> 8) & 0xff;
              map_key_2[10u] = tcpudp_header_1->dst_port & 0xff;
              map_key_2[11u] = (tcpudp_header_1->dst_port >> 8) & 0xff;
              map_key_2[12u] = ipv4_header_1->next_proto_id;
              int map_value_out_1;
              int map_has_this_key__147 = map_get(map, &map_key_2, &map_value_out_1);
              uint8_t hashed_obj[16];
              hashed_obj[0u] = ipv4_header_1->src_addr & 0xff;
              hashed_obj[1u] = (ipv4_header_1->src_addr >> 8) & 0xff;
              hashed_obj[2u] = (ipv4_header_1->src_addr >> 16) & 0xff;
              hashed_obj[3u] = (ipv4_header_1->src_addr >> 24) & 0xff;
              hashed_obj[4u] = ipv4_header_1->dst_addr & 0xff;
              hashed_obj[5u] = (ipv4_header_1->dst_addr >> 8) & 0xff;
              hashed_obj[6u] = (ipv4_header_1->dst_addr >> 16) & 0xff;
              hashed_obj[7u] = (ipv4_header_1->dst_addr >> 24) & 0xff;
              hashed_obj[8u] = tcpudp_header_1->src_port & 0xff;
              hashed_obj[9u] = (tcpudp_header_1->src_port >> 8) & 0xff;
              hashed_obj[10u] = tcpudp_header_1->dst_port & 0xff;
              hashed_obj[11u] = (tcpudp_header_1->dst_port >> 8) & 0xff;
              hashed_obj[12u] = ipv4_header_1->next_proto_id;
              hashed_obj[13u] = 171u;
              hashed_obj[14u] = 171u;
              hashed_obj[15u] = 171u;
              uint32_t LoadBalancedFlow_hash__148 = LoadBalancedFlow_hash(hashed_obj);
              uint32_t chosen_backend__149 = 0u;
              int32_t prefered_backend_found__149 = cht_find_preferred_available_backend(LoadBalancedFlow_hash__148, vector_4, dchain_1, 97u, 32u, &chosen_backend__149);

              // 298
              if (0u == prefered_backend_found__149) {
                // dropping
                return device;
              }

              // 299
              // 300
              else {
                uint32_t new_index__160;
                int out_of_space__160 = !dchain_allocate_new_index(dchain, &new_index__160, now);
                uint8_t* vector_value_out_2 = 0u;
                vector_borrow(vector, new_index__160, (void**)(&vector_value_out_2));
                vector_value_out_2[0u] = ipv4_header_1->src_addr & 0xff;
                vector_value_out_2[1u] = (ipv4_header_1->src_addr >> 8) & 0xff;
                vector_value_out_2[2u] = (ipv4_header_1->src_addr >> 16) & 0xff;
                vector_value_out_2[3u] = (ipv4_header_1->src_addr >> 24) & 0xff;
                vector_value_out_2[4u] = ipv4_header_1->dst_addr & 0xff;
                vector_value_out_2[5u] = (ipv4_header_1->dst_addr >> 8) & 0xff;
                vector_value_out_2[6u] = (ipv4_header_1->dst_addr >> 16) & 0xff;
                vector_value_out_2[7u] = (ipv4_header_1->dst_addr >> 24) & 0xff;
                vector_value_out_2[8u] = tcpudp_header_1->src_port & 0xff;
                vector_value_out_2[9u] = (tcpudp_header_1->src_port >> 8) & 0xff;
                vector_value_out_2[10u] = tcpudp_header_1->dst_port & 0xff;
                vector_value_out_2[11u] = (tcpudp_header_1->dst_port >> 8) & 0xff;
                vector_value_out_2[12u] = ipv4_header_1->next_proto_id;
                vector_value_out_2[13u] = 171u;
                vector_value_out_2[14u] = 171u;
                vector_value_out_2[15u] = 171u;
                uint8_t* vector_value_out_3 = 0u;
                vector_borrow(vector_1, new_index__160, (void**)(&vector_value_out_3));
                vector_value_out_3[0u] = chosen_backend__149 & 0xff;
                vector_value_out_3[1u] = (chosen_backend__149 >> 8) & 0xff;
                vector_value_out_3[2u] = (chosen_backend__149 >> 16) & 0xff;
                vector_value_out_3[3u] = (chosen_backend__149 >> 24) & 0xff;
                vector_return(vector_1, new_index__160, vector_value_out_3);
                map_put(map, vector_value_out_2, new_index__160);
                vector_return(vector, new_index__160, vector_value_out_2);
                uint8_t* vector_value_out_4 = 0u;
                vector_borrow(vector_3, chosen_backend__149, (void**)(&vector_value_out_4));
                vector_return(vector_3, chosen_backend__149, vector_value_out_4);
                int checksum__168 = rte_ipv4_udptcp_cksum(ipv4_header_1, tcpudp_header_1);
                ipv4_header_1->hdr_checksum = checksum__168 & 0xffff;
                ipv4_header_1->dst_addr = vector_value_out_4[8ul];
                ether_header_1->d_addr.addr_bytes[0ul] = vector_value_out_4[2ul];
                ether_header_1->d_addr.addr_bytes[1ul] = vector_value_out_4[3ul];
                ether_header_1->d_addr.addr_bytes[2ul] = vector_value_out_4[4ul];
                ether_header_1->d_addr.addr_bytes[3ul] = vector_value_out_4[5ul];
                ether_header_1->d_addr.addr_bytes[4ul] = vector_value_out_4[6ul];
                ether_header_1->d_addr.addr_bytes[5ul] = vector_value_out_4[7ul];
                ether_header_1->s_addr.addr_bytes[0ul] = 171u;
                ether_header_1->s_addr.addr_bytes[1ul] = 171u;
                ether_header_1->s_addr.addr_bytes[2ul] = 171u;
                ether_header_1->s_addr.addr_bytes[3ul] = 171u;
                ether_header_1->s_addr.addr_bytes[4ul] = 171u;
                ether_header_1->s_addr.addr_bytes[5ul] = 171u;

                // 299
                if (vector_value_out_4[0ul]) {
                  return 1;
                }

                // 300
                else {
                  return 0;
                } // !vector_value_out_4[0ul]

              } // !(0u == prefered_backend_found__149)

            } // !dchain_is_index_allocated__121

          } // !(0u == map_has_this_key__60)

        }

        // 301
        // 302
        // 303
        else {
          uint8_t map_key[4];
          map_key[0u] = ipv4_header_1->src_addr & 0xff;
          map_key[1u] = (ipv4_header_1->src_addr >> 8) & 0xff;
          map_key[2u] = (ipv4_header_1->src_addr >> 16) & 0xff;
          map_key[3u] = (ipv4_header_1->src_addr >> 24) & 0xff;
          int map_value_out;
          int map_has_this_key__184 = map_get(map_1, &map_key, &map_value_out);

          // 301
          // 302
          if (0u == map_has_this_key__184) {
            uint32_t new_index__187;
            int out_of_space__187 = !dchain_allocate_new_index(dchain_1, &new_index__187, now);

            // 301
            if (false == ((out_of_space__187) & (0u == number_of_freed_flows__46))) {
              uint8_t* vector_value_out = 0u;
              vector_borrow(vector_3, new_index__187, (void**)(&vector_value_out));
              vector_value_out[0u] = device & 0xff;
              vector_value_out[1u] = (device >> 8) & 0xff;
              vector_value_out[2u] = ether_header_1->s_addr.addr_bytes[0ul];
              vector_value_out[3u] = ether_header_1->s_addr.addr_bytes[1ul];
              vector_value_out[4u] = ether_header_1->s_addr.addr_bytes[2ul];
              vector_value_out[5u] = ether_header_1->s_addr.addr_bytes[3ul];
              vector_value_out[6u] = ether_header_1->s_addr.addr_bytes[4ul];
              vector_value_out[7u] = ether_header_1->s_addr.addr_bytes[5ul];
              vector_value_out[8u] = ipv4_header_1->src_addr & 0xff;
              vector_value_out[9u] = (ipv4_header_1->src_addr >> 8) & 0xff;
              vector_value_out[10u] = (ipv4_header_1->src_addr >> 16) & 0xff;
              vector_value_out[11u] = (ipv4_header_1->src_addr >> 24) & 0xff;
              vector_return(vector_3, new_index__187, vector_value_out);
              uint8_t* vector_value_out_1 = 0u;
              vector_borrow(vector_2, new_index__187, (void**)(&vector_value_out_1));
              vector_value_out_1[0u] = ipv4_header_1->src_addr & 0xff;
              vector_value_out_1[1u] = (ipv4_header_1->src_addr >> 8) & 0xff;
              vector_value_out_1[2u] = (ipv4_header_1->src_addr >> 16) & 0xff;
              vector_value_out_1[3u] = (ipv4_header_1->src_addr >> 24) & 0xff;
              map_put(map_1, vector_value_out_1, new_index__187);
              vector_return(vector_2, new_index__187, vector_value_out_1);
              // dropping
              return device;
            }

            // 302
            else {
              // dropping
              return device;
            } // !(false == ((out_of_space__187) & (0u == number_of_freed_flows__46)))

          }

          // 303
          else {
            dchain_rejuvenate_index(dchain_1, map_value_out, now);
            // dropping
            return device;
          } // !(0u == map_has_this_key__184)

        } // !(1u != device)

      }

      // 304
      // 305
      // 306
      else {
        uint8_t map_key[4];
        map_key[0u] = ipv4_header_1->src_addr & 0xff;
        map_key[1u] = (ipv4_header_1->src_addr >> 8) & 0xff;
        map_key[2u] = (ipv4_header_1->src_addr >> 16) & 0xff;
        map_key[3u] = (ipv4_header_1->src_addr >> 24) & 0xff;
        int map_value_out;
        int map_has_this_key__220 = map_get(map_1, &map_key, &map_value_out);

        // 304
        // 305
        if (0u == map_has_this_key__220) {
          uint32_t new_index__223;
          int out_of_space__223 = !dchain_allocate_new_index(dchain_1, &new_index__223, now);

          // 304
          if (false == ((out_of_space__223) & (0u == number_of_freed_flows__46))) {
            uint8_t* vector_value_out = 0u;
            vector_borrow(vector_3, new_index__223, (void**)(&vector_value_out));
            vector_value_out[0u] = device & 0xff;
            vector_value_out[1u] = (device >> 8) & 0xff;
            vector_value_out[2u] = ether_header_1->s_addr.addr_bytes[0ul];
            vector_value_out[3u] = ether_header_1->s_addr.addr_bytes[1ul];
            vector_value_out[4u] = ether_header_1->s_addr.addr_bytes[2ul];
            vector_value_out[5u] = ether_header_1->s_addr.addr_bytes[3ul];
            vector_value_out[6u] = ether_header_1->s_addr.addr_bytes[4ul];
            vector_value_out[7u] = ether_header_1->s_addr.addr_bytes[5ul];
            vector_value_out[8u] = ipv4_header_1->src_addr & 0xff;
            vector_value_out[9u] = (ipv4_header_1->src_addr >> 8) & 0xff;
            vector_value_out[10u] = (ipv4_header_1->src_addr >> 16) & 0xff;
            vector_value_out[11u] = (ipv4_header_1->src_addr >> 24) & 0xff;
            vector_return(vector_3, new_index__223, vector_value_out);
            uint8_t* vector_value_out_1 = 0u;
            vector_borrow(vector_2, new_index__223, (void**)(&vector_value_out_1));
            vector_value_out_1[0u] = ipv4_header_1->src_addr & 0xff;
            vector_value_out_1[1u] = (ipv4_header_1->src_addr >> 8) & 0xff;
            vector_value_out_1[2u] = (ipv4_header_1->src_addr >> 16) & 0xff;
            vector_value_out_1[3u] = (ipv4_header_1->src_addr >> 24) & 0xff;
            map_put(map_1, vector_value_out_1, new_index__223);
            vector_return(vector_2, new_index__223, vector_value_out_1);
            // dropping
            return device;
          }

          // 305
          else {
            // dropping
            return device;
          } // !(false == ((out_of_space__223) & (0u == number_of_freed_flows__46)))

        }

        // 306
        else {
          dchain_rejuvenate_index(dchain_1, map_value_out, now);
          // dropping
          return device;
        } // !(0u == map_has_this_key__220)

      } // !device

    }

    // 307
    else {
      // dropping
      return device;
    } // !(0u == ((0u == ((6u == ipv4_header_1->next_proto_id) | (17u == ipv4_header_1->next_proto_id))) | ((4294967262u + packet_length) < 4ul)))

  }

  // 308
  else {
    // dropping
    return device;
  } // !(0u == ((8u != ether_header_1->ether_type) | ((4294967282u + packet_length) < 20ul)))

}
