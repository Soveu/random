#include <iostream>
#include <iomanip>
#include <vector>
#include <stdint.h>

std::vector<uint32_t> get_primes(uint64_t n) {
  std::vector<uint32_t> minPrime(n+1);
  std::vector<uint32_t> primes;

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
  auto primes = get_primes(1 << 16);

  for(const auto& p : primes) {
    std::cout << "0x" << std::hex << (p*p) << ", ";
  }
  std::cout << std::endl;
  std::cout << primes.size() << '\n';

  return 0;
}

