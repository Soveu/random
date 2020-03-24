#include <string>
#include <iostream>

using namespace std::string_literals;
void f(int) {
  std::cout << "int\n";
}
void f(unsigned) {
  std::cout << "unsigned\n";
}

int main() {
  std::string s1("hello world",5); 
  std::string s2("hello world"s,5); 
  
  std::cout<<s1<<s2;

  uint8_t x = 8;
  f(x);
}
