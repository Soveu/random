#include<unistd.h>
#include<stdio.h>
#define BUFLEN 1024

int main(){
  char buf[128];
  gets(buf);

  return 0;
}


