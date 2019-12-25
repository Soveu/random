#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <stdint.h>

struct Pcg32 {
  uint64_t state;
  uint64_t inc; 

  uint32_t random() {
    uint64_t oldstate = this->state;
    // Advance internal state
    this->state = oldstate * 6364136223846793005ULL + (this->inc|1);
    // Calculate output function (XSH RR), uses old state for max ILP
    uint32_t xorshifted = ((oldstate >> 18u) ^ oldstate) >> 27u;
    uint32_t rot = oldstate >> 59u;
    return (xorshifted >> rot) | (xorshifted << ((-rot) & 31));
  }
};

std::vector<uint32_t> make_random_vector(size_t n) {
  std::vector<uint32_t> res(n);
  Pcg32 rand;

  for(auto& x : res) {
    x = rand.random();
  }

  return res;
}

using Clock = std::chrono::high_resolution_clock;

template<typename Iterator>
void insertion_sort(const Iterator begin, const Iterator end) {
  auto i = begin + 1;

  while(i < end) {
    const uint32_t x = *i;
    auto j = i - 1;
    while(j >= begin && x < *j) {
      *(j+1) = *j;
      --j;
    }
    *(j+1) = x;
    ++i;
  }
}

template<typename Iterator>
void stupid_sort(Iterator begin, Iterator end) {
  std::make_heap(begin, end, [](const uint32_t a, const uint32_t b) {
    return a > b;
  });
  insertion_sort(begin, end);
}

int main() {
  const std::vector<uint32_t> orig = make_random_vector(1 << 20);
  std::vector<uint32_t> copy1 = orig;
  std::vector<uint32_t> copy2 = orig;

  auto timep = Clock::now();
  std::sort(copy1.begin(), copy1.end());
  auto duration = std::chrono::duration_cast<std::chrono::microseconds>(Clock::now() - timep);
  std::cout << duration.count() << std::endl;

  timep = Clock::now();
  stupid_sort(copy2.begin(), copy2.end());
  duration = std::chrono::duration_cast<std::chrono::microseconds>(Clock::now() - timep);
  std::cout << duration.count() << std::endl;

  if(copy1 == copy2) {
    std::cout << "Correct!\n";
  }

  return 0;
}
