#include <stdint.h>
#include <stdio.h>

int main() {
  uint16_t marker = 0xBEEF;
  uint64_t ptr = (uint64_t)&marker;
  ptr |= ((uint64_t)marker << 48);
  
  char *p = (char*)ptr;

  printf("%p\n", p);

  return 0;
}

