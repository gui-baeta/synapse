
bool rte_ether_addr_eq(void* a, void* b) ;
uint32_t rte_ether_addr_hash(void* obj) ;
void rte_ether_addr_allocate(void* obj) ;
void DynamicValue_allocate(void* obj) ;
bool StaticKey_eq(void* a, void* b) ;
uint32_t StaticKey_hash(void* obj) ;
void StaticKey_allocate(void* obj) ;
struct Map* map;
struct Vector* vector;
struct Vector* vector_1;
struct Map* map_1;
struct Vector* vector_2;
struct DoubleChain* dchain;

bool nf_init() {
  int map_allocation_succeeded__1 = map_allocate(rte_ether_addr_eq, rte_ether_addr_hash, 65536u, &map);

  // 82
  // 83
  // 84
  // 85
  // 86
  // 87
  if (map_allocation_succeeded__1) {
    int vector_alloc_success__4 = vector_allocate(6u, 65536u, rte_ether_addr_allocate, &vector);

    // 82
    // 83
    // 84
    // 85
    // 86
    if (vector_alloc_success__4) {
      int vector_alloc_success__7 = vector_allocate(2u, 65536u, DynamicValue_allocate, &vector_1);

      // 82
      // 83
      // 84
      // 85
      if (vector_alloc_success__7) {
        int map_allocation_succeeded__10 = map_allocate(StaticKey_eq, StaticKey_hash, 8192u, &map_1);

        // 82
        // 83
        // 84
        if (map_allocation_succeeded__10) {
          int vector_alloc_success__13 = vector_allocate(8u, 8192u, StaticKey_allocate, &vector_2);

          // 82
          // 83
          if (vector_alloc_success__13) {
            int is_dchain_allocated__16 = dchain_allocate(65536u, &dchain);

            // 82
            if (is_dchain_allocated__16) {
              return 1;
            }

            // 83
            else {
              return 0;
            } // !is_dchain_allocated__16

          }

          // 84
          else {
            return 0;
          } // !vector_alloc_success__13

        }

        // 85
        else {
          return 0;
        } // !map_allocation_succeeded__10

      }

      // 86
      else {
        return 0;
      } // !vector_alloc_success__7

    }

    // 87
    else {
      return 0;
    } // !vector_alloc_success__4

  }

  // 88
  else {
    return 0;
  } // !map_allocation_succeeded__1

}

int nf_process(uint16_t device, uint8_t* packet, uint16_t packet_length, int64_t now) {
  struct rte_ether_hdr* ether_header_1 = (struct rte_ether_hdr*)(packet);
  uint8_t map_key[8];
  map_key[0u] = ether_header_1->d_addr.addr_bytes[0ul];
  map_key[1u] = ether_header_1->d_addr.addr_bytes[1ul];
  map_key[2u] = ether_header_1->d_addr.addr_bytes[2ul];
  map_key[3u] = ether_header_1->d_addr.addr_bytes[3ul];
  map_key[4u] = ether_header_1->d_addr.addr_bytes[4ul];
  map_key[5u] = ether_header_1->d_addr.addr_bytes[5ul];
  map_key[6u] = device & 0xff;
  map_key[7u] = (device >> 8) & 0xff;
  int map_value_out;
  int map_has_this_key__34 = map_get(map_1, &map_key, &map_value_out);

  // 90
  // 91
  // 92
  if (device) {

    // 90
    // 91
    if (map_has_this_key__34) {

      // 90
      if (map_value_out & 0xffff == device) {
        // dropping
        return device;
      }

      // 91
      else {
        return 0;
      } // !(map_value_out & 0xffff == device)

    }

    // 92
    else {
      return 0;
    } // !map_has_this_key__34

  }

  // 93
  // 94
  // 95
  else {

    // 93
    // 94
    if (map_has_this_key__34) {

      // 93
      if (0u == map_value_out & 0xffff) {
        // dropping
        return device;
      }

      // 94
      else {
        return 1;
      } // !(0u == map_value_out & 0xffff)

    }

    // 95
    else {
      return 1;
    } // !map_has_this_key__34

  } // !device

}
