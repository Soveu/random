#include <unistd.h>
#include <fcntl.h>
#include <poll.h>

#include <stdio.h>

int main(int argc, char* argv[]){
  char bufs[2][64];

  int pipe1 = open("pipe1", O_RDWR);
  int pipe2 = open("pipe2", O_RDWR);

  if(pipe1 == -1 || pipe2 == -1) {
    perror("pipe");
    return 1;
  }

  struct pollfd fds[2] = {
    [0] = {
      .fd = pipe1,
      .events = POLLIN,
      .revents = 0,
    },
    [1] = {
      .fd = pipe2,
      .events = POLLIN,
      .revents = 0,
    }
  };

  while(1) {
    int pollret = poll(fds, 2, 500);
    if(pollret == -1) {
      perror("pollret");
      return 2;
    }

    if((fds[0].revents & POLLHUP) && (fds[1].revents & POLLHUP)) break;

    for(int i=0; i<2; ++i) {
      if(fds[i].revents & POLLIN) {
        printf("%d is ready!\n", fds[i].fd);
        ssize_t bytes_read = read(fds[i].fd, bufs[i], sizeof(bufs[0]));
        if(bytes_read < 0) return 1;
        write(1, bufs[i], bytes_read);
      }
    }
  }

  const char* msg = "FINISHED\n";
  write(1, msg, sizeof(msg));

  return 0;
}

