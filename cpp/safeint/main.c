#include <iostream>

extern "C" bool is_overflow_flag_set(void);

int main() {
  unsigned short x = 0xFFFF;
  x += 1;

  if(is_overflow_flag_set()) {
    std::cout << "OVERFLOW1\n";
  }
  std::cout << x << '\n';

  short y = 0x7FFF;
  y += 1;

  if(is_overflow_flag_set()) {
    std::cout << "OVERFLOW2\n";
  }
  std::cout << y << '\n';

  y += 0x8000;

  if(is_overflow_flag_set()) {
    std::cout << "OVERFLOW3\n";
  }
  std::cout << y << '\n';

  return 0;
}

