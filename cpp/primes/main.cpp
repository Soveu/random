#include <iostream>
#include <vector>

uint64_t misses = 0;

bool is_prime(int64_t x, const std::vector<int64_t>& primes) {
  for(const auto& prime : primes) {
    if(x % prime == 0) {
      return false;
    }

    misses += 1;
  }

  return true;
}

std::vector<int64_t> get_primes(int64_t n) {
  std::vector<int64_t> primes;
  primes.reserve(65536);
  primes.push_back(2);

  int64_t number = 3;

  while(number < n) {
    if(is_prime(number, primes)) {
      primes.push_back(number);
    }

    number += 2;
  }

  return primes;
}

int main() {
  auto primes = get_primes(1000000);
  std::cout << primes.size() << " primes generated" << std::endl;
  std::cout << misses << " misses\n";
  std::cout << (static_cast<double>(misses) / primes.size()) << " misses per prime\n";
  std::cout << (static_cast<double>(misses) / primes.back()) << " misses per number\n";
  return 0;
}

