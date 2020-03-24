#include <stdint.h>

template<typename Int>
Int gcd(Int a, Int b) {
  while(b != 0) {
    auto c = a % b;
    a = b;
    b = c;
  }

  return a;
}

template<typename Int>
Int lcm(Int a, Int b) {
  return (a / gcd(a, b)) * b;
}

template <typename Integer>
struct Fraction {
  Integer numerator;
  Integer denumerator;

  template<typename Int>
  Fraction<Integer>& operator+=(Int x) {
    numerator += x*denumerator;
    return *this;
  }
  template<typename Int>
  Fraction<Integer>& operator-=(Int x) {
    numerator -= x*denumerator;
    return *this;
  }
  template<typename Int>
  Fraction<Integer>& operator*=(Int x) {
    auto g = gcd(x, denumerator);
    denumerator /= g;
    numerator *= (x / g);
    return *this;
  }
  template<typename Int>
  Fraction<Integer>& operator/=(Int x) {
    auto g = gcd(x, numerator);
    numerator /= g;
    denumerator *= (x / g);
    return *this;
  }

  template<typename Int>
  Fraction<Int> operator+(Int x) const {
    Fraction<Int> f = *this;
    return f += x;
  }
  template<typename Int>
  Fraction<Int> operator-(Int x) const {
    Fraction<Int> f = *this;
    return f -= x;
  }
  template<typename Int>
  Fraction<Int> operator*(Int x) const {
    Fraction<Int> f = *this;
    return f *= x;
  }
  template<typename Int>
  Fraction<Int> operator/(Int x) const {
    Fraction<Int> f = *this;
    return f /= x;
  }

  template<typename Int>
  Fraction<Integer>& operator+=(const Fraction<Int>& f) {
    auto l = lcm(denumerator, f.denumerator);
    numerator *= (l / denumerator);
    numerator += f.numerator * (l / f.denumerator);
    return *this;
  }
  template<typename Int>
  Fraction<Integer>& operator-=(const Fraction<Int>& f) {
    auto l = lcm(denumerator, f.denumerator);
    numerator *= (l / denumerator);
    numerator -= f.numerator * (l / f.denumerator);
    return *this;
  }
  template<typename Int>
  Fraction<Integer>& operator*=(const Fraction<Int>& f) {
    auto g1 = gcd(numerator, f.denumerator);
    auto g2 = gcd(denumerator, f.numerator);
    numerator /= g1;
    denumerator /= g2;
    numerator *= (f.numerator / g2);
    denumerator *= (f.denumerator / g1);
    return *this;
  }
  template<typename Int>
  Fraction<Integer>& operator/=(const Fraction<Int>& f) {
    auto g1 = gcd(numerator, f.numerator);
    auto g2 = gcd(denumerator, f.denumerator);
    numerator /= g1;
    denumerator /= g2;
    numerator *= (f.denumerator / g2);
    denumerator *= (f.numerator / g1);
    return *this;
  }

  template<typename Int>
  Fraction<Int> operator+(const Fraction<Int>& f) const {
    Fraction<Int> x = *this;
    return x += f;
  }
  template<typename Int>
  Fraction<Int> operator-(const Fraction<Int>& f) const {
    Fraction<Int> x = *this;
    return x -= f;
  }
  template<typename Int>
  Fraction<Int> operator*(const Fraction<Int>& f) const {
    Fraction<Int> x = *this;
    return x *= f;
  }
  template<typename Int>
  Fraction<Int> operator/(const Fraction<Int>& f) const {
    Fraction<Int> x = *this;
    return x /= f;
  }
};

