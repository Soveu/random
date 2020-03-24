#include <iostream>
#include <vector>

const int boxes[] = {4,6,9,20};
const int MAX = 0xFFFFFF;

int main() {
  std::vector<int> dp(100, MAX);
  dp[0] = 0;

  for(int i=1; i<100; ++i) {
    int min = MAX;
    for(int box : boxes) {
      if(i>=box) {
        min = std::min(min, dp[i-box]+1);
      }
    }
    dp[i] = min;
  }

  for(int i=1; i<100; ++i) {
    std::cout << i << ": " << dp[i] << '\n';
  }
}

