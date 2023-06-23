
bool nf_init() {
  return 1;
}

int nf_process(uint16_t device, uint8_t* packet, uint16_t packet_length, int64_t now) {
  struct rte_ether_hdr* ether_header_1 = (struct rte_ether_hdr*)(packet);

  // 32
  if (device) {
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

  // 33
  else {
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
  } // !device

}
