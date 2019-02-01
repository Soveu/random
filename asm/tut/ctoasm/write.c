#include<unistd.h>

void fun(int a, int b, int c, int d, int e, int f, int g) {
  char str[] = "Hello World!\n";

  write(1, str, sizeof(str)); // 1 - stdout fd

  return;
}

int main() {
  fun(0, 1, 2, 3, 4, 5, 6);

  return 0;
}

