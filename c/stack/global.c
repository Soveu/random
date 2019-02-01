#include<stdio.h>

void* globalVariable = 0;

int main() {
  void* localVariable = 0;

  printf("global: %X \nlocal:  %X\ndelta:  %d\n", 
      &globalVariable, &localVariable, &globalVariable - &localVariable);

  return 0;
}

