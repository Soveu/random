#include<vector>
#include<iostream>

int main() {
  std::vector<int> vec;
  vec.resize(1024 * 1024);
  vec[1000000] = 1;

  vec[1024 * 1024 + 2] = 1;
  std::cout << "HELLO\n";
  vec.at(1024 * 1024 + 2) = 1;

  return 0;
}

