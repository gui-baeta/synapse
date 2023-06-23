
bool flow_eq(void* a, void* b) ;
uint32_t flow_hash(void* obj) ;
void flow_allocate(void* obj) ;
struct Map* map;
struct Vector* vector;

bool nf_init() {
  int map_allocation_succeeded__1 = map_allocate(flow_eq, flow_hash, 65536u, &map);

  // 68
  // 69
  if (map_allocation_succeeded__1) {
    int vector_alloc_success__4 = vector_allocate(16u, 65536u, flow_allocate, &vector);

    // 68
    if (vector_alloc_success__4) {
      return 1;
    }

    // 69
    else {
      return 0;
    } // !vector_alloc_success__4

  }

  // 70
  else {
    return 0;
  } // !map_allocation_succeeded__1

}

int nf_process(uint16_t device, uint8_t* packet, uint16_t packet_length, int64_t now) {
  struct rte_ether_hdr* ether_header_1 = (struct rte_ether_hdr*)(packet);

  // 72
  // 73
  // 74
  // 75
  if (0u == ((8u != ether_header_1->ether_type) | ((4294967282u + packet_length) < 20ul))) {
    struct rte_ipv4_hdr* ipv4_header_1 = (struct rte_ipv4_hdr*)(packet + 14u);

    // 72
    // 73
    // 74
    if (0u == ((0u == ((6u == ipv4_header_1->next_proto_id) | (17u == ipv4_header_1->next_proto_id))) | ((4294967262u + packet_length) < 4ul))) {
      struct tcpudp_hdr* tcpudp_header_1 = (struct tcpudp_hdr*)(packet + (14u + 20u));
      uint8_t map_key[15];
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
      map_key[12u] = device & 0xff;
      map_key[13u] = (device >> 8) & 0xff;
      map_key[14u] = ipv4_header_1->next_proto_id;
      int map_value_out;
      int map_has_this_key__30 = map_get(map, &map_key, &map_value_out);

      // 72
      if (0u == map_has_this_key__30) {
        // dropping
        return device;
      }

      // 73
      // 74
      else {

        // 73
        if (device) {
          return 0;
        }

        // 74
        else {
          return 1;
        } // !device

      } // !(0u == map_has_this_key__30)

    }

    // 75
    else {
      // dropping
      return device;
    } // !(0u == ((0u == ((6u == ipv4_header_1->next_proto_id) | (17u == ipv4_header_1->next_proto_id))) | ((4294967262u + packet_length) < 4ul)))

  }

  // 76
  else {
    // dropping
    return device;
  } // !(0u == ((8u != ether_header_1->ether_type) | ((4294967282u + packet_length) < 20ul)))

}
