#include <iostream>
#include <set>
#include <chrono>

using Clock = std::chrono::high_resolution_clock;
using TimePoint = std::chrono::time_point<Clock>;
using Duration = std::chrono::duration<double>;

double seconds_elapsed(const TimePoint& start) {
  auto end = Clock::now();
  Duration ret = end - start;
  return ret.count();
}

int main() {
  std::cin.tie(0);
  std::ios_base::sync_with_stdio(false);

  auto start = Clock::now();
  size_t sz;
  std::string s;
  std::set<std::string> set;

  std::cin >> sz;
  for(size_t i=0; i<sz; ++i) {
    std::cin >> s;
    set.insert(s);
  }

  std::cout << "Inserted elements - "<< seconds_elapsed(start) << "s)" << std::endl;
  std::cout << "Got " << set.size() << " entries" << std::endl;

  size_t hits = 0;

  std::cin >> sz;
  for(size_t i=0; i<sz; ++i) {
    std::cin >> s;
    bool contains = set.contains(s);
    hits += contains;
  }

  std::cout << "Hits: " << hits << std::endl;
  std::cout << "Finished ("<< seconds_elapsed(start) << "s)" << std::endl;
}

