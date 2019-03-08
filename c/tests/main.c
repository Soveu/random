#include "pipedchild.h"

#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#include <stdio.h>
#include <string.h>

#define BUFSIZE (4096)

int main() {
  Pchild tester, testee;
  char buffer[BUFSIZE], buffee[BUFSIZE];
  size_t writter=0, writtee=0;
  ssize_t a, b;
  char buf[BUFSIZE];
  int status;

  char msg[] = "whoami; echo Hello\n";

  if(spawnPipedChild(&tester, "/bin/bash", 0, 0) == -1)
    return -1;

  if(spawnPipedChild(&testee, "/bin/bash", 0, 0) == -1)
    return -1;

  /*
  write(tester.pipeIn, msg, sizeof(msg));
  write(testee.pipeIn, msg, sizeof(msg));
  close(testee.pipeIn);
  close(tester.pipeIn);
  */
  size_t checkedTill=0;
  bool canRead = true;
  do {
    if(canRead) {
      ssize_t n = read(0, buf, BUFSIZE);
      
      if(n <= 0) {
        if(close(tester.pipeIn) + close(testee.pipeIn) < 0) {
          perror("close childin");
          return 4;
        }
        canRead = false;
      } 
      else {
        write(tester.pipeIn, buf, n);
        write(testee.pipeIn, buf, n);
      }
    }

    a = read(tester.pipeOut, buffer + writter, BUFSIZE-writter);
    b = read(testee.pipeOut, buffee + writtee, BUFSIZE-writtee);

    if(a == -1 || b == -1) {
      perror("child read");
      return 3;
    }

    writter += a;
    writtee += b;
    size_t toCheck = (writter < writtee ? writter : writtee) - checkedTill;

    if(memcmp(buffer + checkedTill, buffee + checkedTill, toCheck) == 0)
      write(1, "OK!\n", 4);
    else
      write(1, "FAIL\n", 5);

    checkedTill += toCheck;
  } while(a > 0 && b > 0);

  waitpid(tester.pid, &status, 0);
  waitpid(testee.pid, &status, 0);

  return 0;
}

