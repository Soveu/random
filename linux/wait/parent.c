#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
  pid_t child = fork();
  if(child == 0) {
    _exit(execvp("./child", 0));
  }

  sleep(5);

  int status = -1;
  puts("Waiting for child...");
  int ret = waitpid(child, &status, WNOHANG);
  if(ret != 0) {
    printf("waitpid returned %d, child returned with status %d\n", ret, status);
  }
  //printf("Child returned with status %d\n", status);

  status = -1;
  if(waitpid(child, &status, 0) != child) {
    printf("Fail, status=%d\n", status);
    perror("Fail");
    return 2;
  }
  printf("Child returned with status %d\n", status);

  return 0;
}

