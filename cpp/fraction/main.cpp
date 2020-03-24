#include <iostream>

#include "fraction.hpp"

template <typename Int>
std::ostream& operator<<(std::ostream& out, const Fraction<Int>& f) {
  return out << f.numerator << '/' << f.denumerator;
}

int main() {
  Fraction<int> f1{1, 1};
  f1 /= 3;
  f1 *= 2;

  Fraction<int> f2{2, 3};
  f1 /= f2;
  f1 *= 420;
  f1 /= 69;

  std::cout << f1 << std::endl;

  return 0;
}

