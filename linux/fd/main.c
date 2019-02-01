#include<unistd.h>
#include<fcntl.h>

int main(int argc, char* argv[]){
  int fd = open("foo", O_RDWR);

  if(fd == -1) return 1;
  if(dup2(fd, 0) == -1) return 2;
  if(close(fd) == -1) return 3;
  if(execvp("/bin/bash", argv) == -1) return 4;

  return 0;
}

