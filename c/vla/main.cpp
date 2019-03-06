#include<iostream>

int main(){
  size_t x;

  std::cin >> x;

  int foo[x]{0};

  return sizeof(foo);
}

