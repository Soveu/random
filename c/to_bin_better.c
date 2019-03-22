void to_bin_better(uint8_t n, char *output) { 
  *(uint64_t*)output = 3472328296227680304ULL + (((n * 9241421688590303745ULL) / 128) & 72340172838076673ULL);
}

void to_bin_better(uint8_t n, char *output) { 
  *(uint64_t*)output = 0x3030303030303030ULL + 
    (((n * 0x8040201008040201ULL) / 128) & 0x101010101010101ULL);
}
