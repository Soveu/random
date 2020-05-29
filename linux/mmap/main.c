#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>

#include <stdio.h>

int main() {
  void* a = mmap(0, 4096, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, 0, 0);
  if(a == MAP_FAILED) {
    perror("mmap");
    return 1;
  }

  printf("%p\n", a);
  printf("%p\n", &a);

  return 0;
}

