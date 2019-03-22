#include <unistd.h>
#include <sys/ptrace.h>
#include <sys/wait.h>
#include <sys/types.h>

#include <stdio.h>

pid_t spawn_child(char* name, char** argv, char** envp) {
  pid_t child = fork();

  if(child == 0) {
    /*
    if(ptrace(PTRACE_TRACEME, 0, 0, 0) == -1) {
      perror("ptrace(PTRACE_TRACEME)");
    }
    */
    if(execve(name, argv, envp) == -1) {
      perror("execve");
    }
    _exit(2);
  }

  return child;
}

int main(int argc, char** argv, char** envp) {
  if(argc < 2) {
    return 1;
  }

  pid_t child = spawn_child(argv[1], NULL, envp);
  if(child == -1) {
    perror("fork");
    return 2;
  }

  if(ptrace(PTRACE_ATTACH, child, 0, 0) == -1) {
    perror("ptrace(PTRACE_ATTACH)");
    return 3;
  }
  puts("Attaching successful!");

  int status;
  for(;;) {
    if(ptrace(PTRACE_SYSCALL, child, 0, 0) == -1) {
      perror("ptrace(PTRACE_SYSCALL)");
      return 4;
    }
    if(waitpid(child, &status, 0) == -1) {
      perror("waitpid");
      return 5;
    }

    if(WIFEXITED(status)) {
      printf("tracee exited normally with code %d\n", WEXITSTATUS(status));
      break;
    }

    if(WIFSTOPPED(status) && WSTOPSIG(status) == SIGTRAP) {
      puts("SYSCALL");
    }
  }

  return 0;
}

