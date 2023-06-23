
bool rte_ether_addr_eq(void* a, void* b) ;
uint32_t rte_ether_addr_hash(void* obj) ;
void rte_ether_addr_allocate(void* obj) ;
void DynamicValue_allocate(void* obj) ;
struct Map* map;
struct Vector* vector;
struct Vector* vector_1;
struct DoubleChain* dchain;

bool nf_init() {
  int map_allocation_succeeded__1 = map_allocate(rte_ether_addr_eq, rte_ether_addr_hash, 65536u, &map);

  // 180
  // 181
  // 182
  // 183
  if (map_allocation_succeeded__1) {
    int vector_alloc_success__4 = vector_allocate(6u, 65536u, rte_ether_addr_allocate, &vector);

    // 180
    // 181
    // 182
    if (vector_alloc_success__4) {
      int vector_alloc_success__7 = vector_allocate(2u, 65536u, DynamicValue_allocate, &vector_1);

      // 180
      // 181
      if (vector_alloc_success__7) {
        int is_dchain_allocated__10 = dchain_allocate(65536u, &dchain);

        // 180
        if (is_dchain_allocated__10) {
          return 1;
        }

        // 181
        else {
          return 0;
        } // !is_dchain_allocated__10

      }

      // 182
      else {
        return 0;
      } // !vector_alloc_success__7

    }

    // 183
    else {
      return 0;
    } // !vector_alloc_success__4

  }

  // 184
  else {
    return 0;
  } // !map_allocation_succeeded__1

}

int nf_process(uint16_t device, uint8_t* packet, uint16_t packet_length, int64_t now) {
  struct rte_ether_hdr* ether_header_1 = (struct rte_ether_hdr*)(packet);
  int number_of_freed_flows__28 = expire_items_single_map(dchain, vector, map, now - 100000000000ul);
  uint8_t map_key[6];
  map_key[0u] = ether_header_1->s_addr.addr_bytes[0ul];
  map_key[1u] = ether_header_1->s_addr.addr_bytes[1ul];
  map_key[2u] = ether_header_1->s_addr.addr_bytes[2ul];
  map_key[3u] = ether_header_1->s_addr.addr_bytes[3ul];
  map_key[4u] = ether_header_1->s_addr.addr_bytes[4ul];
  map_key[5u] = ether_header_1->s_addr.addr_bytes[5ul];
  int map_value_out;
  int map_has_this_key__29 = map_get(map, &map_key, &map_value_out);

  // 186
  // 187
  // 188
  // 189
  // 190
  // 191
  // 192
  // 193
  // 194
  // 195
  // 196
  // 197
  if (0u == map_has_this_key__29) {
    uint32_t new_index__32;
    int out_of_space__32 = !dchain_allocate_new_index(dchain, &new_index__32, now);

    // 186
    // 187
    // 188
    // 189
    // 190
    // 191
    if (false == ((out_of_space__32) & (0u == number_of_freed_flows__28))) {
      uint8_t* vector_value_out = 0u;
      vector_borrow(vector, new_index__32, (void**)(&vector_value_out));
      vector_value_out[0u] = ether_header_1->s_addr.addr_bytes[0ul];
      vector_value_out[1u] = ether_header_1->s_addr.addr_bytes[1ul];
      vector_value_out[2u] = ether_header_1->s_addr.addr_bytes[2ul];
      vector_value_out[3u] = ether_header_1->s_addr.addr_bytes[3ul];
      vector_value_out[4u] = ether_header_1->s_addr.addr_bytes[4ul];
      vector_value_out[5u] = ether_header_1->s_addr.addr_bytes[5ul];
      uint8_t* vector_value_out_1 = 0u;
      vector_borrow(vector_1, new_index__32, (void**)(&vector_value_out_1));
      vector_value_out_1[0u] = device & 0xff;
      vector_value_out_1[1u] = (device >> 8) & 0xff;
      map_put(map, vector_value_out, new_index__32);
      vector_return(vector, new_index__32, vector_value_out);
      vector_return(vector_1, new_index__32, vector_value_out_1);
      uint8_t map_key_1[6];
      map_key_1[0u] = ether_header_1->d_addr.addr_bytes[0ul];
      map_key_1[1u] = ether_header_1->d_addr.addr_bytes[1ul];
      map_key_1[2u] = ether_header_1->d_addr.addr_bytes[2ul];
      map_key_1[3u] = ether_header_1->d_addr.addr_bytes[3ul];
      map_key_1[4u] = ether_header_1->d_addr.addr_bytes[4ul];
      map_key_1[5u] = ether_header_1->d_addr.addr_bytes[5ul];
      int map_value_out_1;
      int map_has_this_key__40 = map_get(map, &map_key_1, &map_value_out_1);

      // 186
      // 187
      if (0u == map_has_this_key__40) {

        // 186
        if (device) {
          return 0;
        }

        // 187
        else {
          return 1;
        } // !device

      }

      // 188
      // 189
      // 190
      // 191
      else {
        uint8_t* vector_value_out_2 = 0u;
        vector_borrow(vector_1, map_value_out_1, (void**)(&vector_value_out_2));
        vector_return(vector_1, map_value_out_1, vector_value_out_2);

        // 188
        // 189
        if (device) {

          // 188
          if (vector_value_out_2 != device) {
            return 0;
          }

          // 189
          else {
            // dropping
            return device;
          } // !(vector_value_out_2 != device)

        }

        // 190
        // 191
        else {

          // 190
          if (((uint16_t*)(vector_value_out_2))[0]) {
            return 1;
          }

          // 191
          else {
            // dropping
            return device;
          } // !((uint16_t*)(vector_value_out_2))[0]

        } // !device

      } // !(0u == map_has_this_key__40)

    }

    // 192
    // 193
    // 194
    // 195
    // 196
    // 197
    else {
      uint8_t map_key_1[6];
      map_key_1[0u] = ether_header_1->d_addr.addr_bytes[0ul];
      map_key_1[1u] = ether_header_1->d_addr.addr_bytes[1ul];
      map_key_1[2u] = ether_header_1->d_addr.addr_bytes[2ul];
      map_key_1[3u] = ether_header_1->d_addr.addr_bytes[3ul];
      map_key_1[4u] = ether_header_1->d_addr.addr_bytes[4ul];
      map_key_1[5u] = ether_header_1->d_addr.addr_bytes[5ul];
      int map_value_out_1;
      int map_has_this_key__85 = map_get(map, &map_key_1, &map_value_out_1);

      // 192
      // 193
      if (0u == map_has_this_key__85) {

        // 192
        if (device) {
          return 0;
        }

        // 193
        else {
          return 1;
        } // !device

      }

      // 194
      // 195
      // 196
      // 197
      else {
        uint8_t* vector_value_out = 0u;
        vector_borrow(vector_1, map_value_out_1, (void**)(&vector_value_out));
        vector_return(vector_1, map_value_out_1, vector_value_out);

        // 194
        // 195
        if (device) {

          // 194
          if (vector_value_out != device) {
            return 0;
          }

          // 195
          else {
            // dropping
            return device;
          } // !(vector_value_out != device)

        }

        // 196
        // 197
        else {

          // 196
          if (((uint16_t*)(vector_value_out))[0]) {
            return 1;
          }

          // 197
          else {
            // dropping
            return device;
          } // !((uint16_t*)(vector_value_out))[0]

        } // !device

      } // !(0u == map_has_this_key__85)

    } // !(false == ((out_of_space__32) & (0u == number_of_freed_flows__28)))

  }

  // 198
  // 199
  // 200
  // 201
  // 202
  // 203
  else {
    dchain_rejuvenate_index(dchain, map_value_out, now);
    uint8_t map_key_1[6];
    map_key_1[0u] = ether_header_1->d_addr.addr_bytes[0ul];
    map_key_1[1u] = ether_header_1->d_addr.addr_bytes[1ul];
    map_key_1[2u] = ether_header_1->d_addr.addr_bytes[2ul];
    map_key_1[3u] = ether_header_1->d_addr.addr_bytes[3ul];
    map_key_1[4u] = ether_header_1->d_addr.addr_bytes[4ul];
    map_key_1[5u] = ether_header_1->d_addr.addr_bytes[5ul];
    int map_value_out_1;
    int map_has_this_key__131 = map_get(map, &map_key_1, &map_value_out_1);

    // 198
    // 199
    if (0u == map_has_this_key__131) {

      // 198
      if (device) {
        return 0;
      }

      // 199
      else {
        return 1;
      } // !device

    }

    // 200
    // 201
    // 202
    // 203
    else {
      uint8_t* vector_value_out = 0u;
      vector_borrow(vector_1, map_value_out_1, (void**)(&vector_value_out));
      vector_return(vector_1, map_value_out_1, vector_value_out);

      // 200
      // 201
      if (device) {

        // 200
        if (vector_value_out != device) {
          return 0;
        }

        // 201
        else {
          // dropping
          return device;
        } // !(vector_value_out != device)

      }

      // 202
      // 203
      else {

        // 202
        if (((uint16_t*)(vector_value_out))[0]) {
          return 1;
        }

        // 203
        else {
          // dropping
          return device;
        } // !((uint16_t*)(vector_value_out))[0]

      } // !device

    } // !(0u == map_has_this_key__131)

  } // !(0u == map_has_this_key__29)

}
