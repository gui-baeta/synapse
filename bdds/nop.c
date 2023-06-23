
bool nf_init() {
  return 1;
}

int nf_process(uint16_t device, uint8_t* packet, uint16_t packet_length, int64_t now) {

  // 29
  if (device) {
    return 0;
  }

  // 30
  else {
    return 1;
  } // !device

}
