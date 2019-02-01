#include<unistd.h>

int main() {
  char buf[32];
  
  int size = read(0, buf, 30);
  write(1, buf, size);

  return 0;
}

