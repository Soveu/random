#include<stdio.h>

struct Empty {};

int main(){
  struct Empty e1, e2;

  printf("%X %X", &e1, &e2);

  return 0;
}

