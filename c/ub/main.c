#include<stdio.h>

void foo(int a, int b){
  printf("%d %d\n", a, b);
}

int main() {
  int i = 1;
  foo(++i, i--);
}

