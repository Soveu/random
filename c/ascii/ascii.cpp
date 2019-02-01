#include<fstream>

int main(){
  std::ofstream cout("/dev/stdout");

  for(char c=0x20; !(c & (1 << 7)); ++c){
    cout << (void*)c << ' ' << c << ' ' << (void*)(c & 0x1f) << ' ' << (void*)(c ^ 32) << '\n';
  }

  return 0;
}

// ASCII letters range = <0x41; 0x7a> - <0x5b; 0x60>
//                     = <0x41; 0x5a> v <0x61; 0x7a>
//
// 41 = 0100_0001
// 5a = 0101_1010
//
// 5b = 0101_1011
// 60 = 0110_0000
//
// 61 = 0110_0001
// 7a = 0111_1010
//
