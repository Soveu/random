#include<stdio.h>

struct Empty{};

int main(){
  printf("%d\n", sizeof(Empty{}));

  return 0;
}

