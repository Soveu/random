#include <iostream>
#include <vector>
#include <stdint.h>

std::vector<uint64_t> get_primes(uint64_t n) {
  std::vector<uint64_t> minPrime(n+1);
  std::vector<uint64_t> primes;

  primes.reserve(n >> 3);

  for(uint64_t number=2; number <= n; ++number) {
    if(minPrime[number] == 0) {
      minPrime[number] = number;
      primes.push_back(number);
    }

    uint64_t j=0;
    while(j < primes.size() && primes[j] <= minPrime[number] && number*primes[j] <= n) {
      minPrime[number * primes[j]] = primes[j];
      j += 1;
    }
  }

  return primes;
}

int main() {
  auto primes = get_primes(1ULL << 22);
  std::cout << primes.size() << '\n';

  return 0;
}
