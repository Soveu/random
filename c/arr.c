#include<array>
#include<iostream>

int main () {
  std::array<int, 3> arr;

  for(int i=0; i<5; ++i) {
    std::cout << arr.at(i) << ' ';
  }

  std::cout << std::endl;

  return 0;
}

/*
int arr[3];

arr[3] = 0xDEADBEEF;
*(arr + 3) = 0xDEADBEEF;
*/
