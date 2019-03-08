#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>

int doChildThings(int pipefd[2]);

int main() {
  char buf[16];
  int pipefd[2];
  if(pipe(pipefd) == -1)
    return 1;

  pid_t child = fork();
  if(child == 0)
    return doChildThings(pipefd);

  write(pipefd[1], "Hello World!\n", 13);
  close(pipefd[1]);

  ssize_t n = read(pipefd[0], buf, sizeof(buf));
  write(1, buf, n);

  return 0;
}

int doChildThings(int pipefd[2]) {
  char buf[16];
  ssize_t n = read(pipefd[0], buf, sizeof(buf));

  for(int i=0; i<n-1; ++i)
    buf[i]++;

  write(pipefd[1], buf, n);
  close(pipefd[1]);

  return 0;
}

