#include<fstream>
#include<stdint.h>

void rec(uint64_t* i, std::ofstream* out){
  char buf[1024];

  (*i) += 1;
  *out << *i << '\n';
  return rec(i, out);
}

int main(){
  uint64_t x = 0;
  std::ofstream cout("/dev/stdout");

  rec(&x, &cout);

  return 0;
}

