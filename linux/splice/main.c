#include <unistd.h>
#include <fcntl.h>

#include <stdio.h>

int main() {
  int fd = open("something.txt", O_RDWR | O_CREAT, 0666);
  perror("open");

  while(splice(0 /*stdin*/, 0, fd, 0, 1, 0) > 0) {};

  perror("splice");
}

