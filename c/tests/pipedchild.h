#pragma once
#include <sys/types.h>

typedef struct{
  pid_t pid;
  int   pipeIn;
  int   pipeOut;
} Pchild;

int spawnPipedChild(Pchild* pc, const char* name, char* const* argv, char* const* envp);
