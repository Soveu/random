#include<stdio.h>
#include<unistd.h>

int main(){
  char* args[] = {
    "execve",
    0
  };

  char* envs[] = {
    0
  };

  puts("Running execve");
  int x = execve("./hello", args, envs);
  printf("Returning with x = %d\n", x);
  return 0;
}
