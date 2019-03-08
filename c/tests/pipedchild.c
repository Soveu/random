#include "pipedchild.h"

#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>

int spawnPipedChild(Pchild* pc, const char* name, char* const* argv, char* const* envp){
  int childIn[2], childOut[2];
  pid_t child;
  
  if(pipe(childIn) + pipe(childOut) < 0)
    return -1;

  child = fork();

  if(child == -1)
    return -1;

  if(child == 0) {
    /* Child */
    dup2(childIn[0], 0);
    dup2(childOut[1], 1);
    dup2(childOut[1], 2);

    close(childIn[0]);
    close(childIn[1]);
    close(childOut[0]);
    close(childOut[1]);

    _exit(execve(name, argv, envp));
  }
  else {
    /* Parent */
    close(childIn[0]);
    close(childOut[1]);

    pc->pid = child;
    pc->pipeIn = childIn[1];
    pc->pipeOut = childOut[0];
  }

  return 0;
}

