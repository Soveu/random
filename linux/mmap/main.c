#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>

int main() {
  void* a = mmap(0, sysconf(_SC_PAGESIZE), PROT_READ | PROT_WRITE, MAP_PRIVATE, 0, 0);
  if(a == MAP_FAILED) {
    perror("mmap");
    return 1;
  }

  write(1, a, 1024);

  return 0;
}

