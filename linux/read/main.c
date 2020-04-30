#include <unistd.h>
#include <fcntl.h>

#include <stdio.h>

const size_t N = 4096;

int main() {
  /* set stdin to not block read() */
  int flags = fcntl(0, F_GETFD, 0);
  fcntl(0, F_SETFD, flags | O_NONBLOCK);

  char buf[N];
  size_t bytes_written = 0;

  puts("Reading until it would block");

  for (;;) {
    ssize_t x = read(0, buf + bytes_written, sizeof(buf) - bytes_written);

    /* bytes read */
    if(x > 0) {
      bytes_written += x;
      continue;
    }

    /* EOF */
    if(x == 0) break;
    /* Blocking read would happen */
    if(EAGAIN == errno) break;

    perror("first read");
    return 1;
  }

  return 0;
}

