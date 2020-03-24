#include <iostream>
#include <vector>
#include <stdint.h>

int64_t marks = 0;

std::vector<uint64_t> get_primes(uint64_t n) {
  n += 1;
  std::vector<bool> isntPrime(n);
  std::vector<uint64_t> primes;

  for(size_t i=4; i<isntPrime.size(); i += 2) {
    isntPrime[i] = true;
  }
  primes.reserve(n >> 3);
  primes.push_back(2);

  for(uint64_t number = 3; number < n; number += 2) {
    if(isntPrime[number]) continue;

    for(uint64_t i = number*3; i<isntPrime.size(); i += number) {
      isntPrime[i] = true;
      marks += 1;
    }

    primes.push_back(number);
  }

  return primes;
}

int main() {
  auto primes = get_primes(1ULL << 29);
  std::cout << primes.size() << '\n';
  std::cout << marks << " marks\n";
  std::cout << static_cast<double>(marks) / primes.size() << " marks per prime\n";
  std::cout << static_cast<double>(marks) / primes.back() << " marks per number\n";

  return 0;
}

