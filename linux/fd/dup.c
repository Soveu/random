#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <stdio.h>

struct S {
  char buf[64];
  int fd;
};

int main() {
  int orig = open("plik.txt", O_RDONLY);

  if(orig == -1) {
    perror("orig");
    return 1;
  }

  struct S s[2];

  for(int i=0; i<2; ++i) {
    //s[i].fd = dup(orig);
    s[i].fd = open("plik.txt", O_RDONLY);
    ssize_t bytes_read = read(s[i].fd, s[i].buf, sizeof(s[i].buf));
    write(0 /* stdout */, s[i].buf, bytes_read);
    printf("\nbytes read=%d\n", bytes_read);
  }

  return 0;
}

