#include <iostream>
#include <vector>
#include <stdint.h>

std::vector<uint32_t> get_primes(uint64_t n) {
  n += 1;
  std::vector<bool> isntPrime(n);
  std::vector<uint32_t> primes;

  for(size_t i=4; i<isntPrime.size(); i += 2) {
    isntPrime[i] = true;
  }
  primes.reserve(n >> 3);
  primes.push_back(2);

  for(uint64_t number = 3; number < n; number += 2) {
    if(isntPrime[number]) continue;

    for(uint64_t i = number*3; i<isntPrime.size(); i += number) {
      isntPrime[i] = true;
    }

    primes.push_back(number);
  }

  return primes;
}

int main() {
  auto primes = get_primes(1000 * 1000 * 1000);
  std::cout << primes.size() << '\n';

  return 0;
}

