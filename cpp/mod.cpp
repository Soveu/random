#include <iostream>

int proper_mod(int a, int b) {
  a %= b;
  return (a < 0 ? a+b : a);
}

int main() {
  for(int i=6; i>-10; --i) {
    std::cout << i << ' ' << proper_mod(i,3) << '\n';
  }
}

