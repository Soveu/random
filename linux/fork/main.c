#include<stdio.h>

#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>
#include<signal.h>

int main(){
  char foo[] = "A string that the whole family has!";
  pid_t child = fork();
  int status;
  
  if(child == 0){
    puts("Hello from the child!");
    puts(foo);
    sleep(3);
    puts("Exiting child...");
    return 3;
  } else {
    puts("Hello from parent!");
    puts("Waiting for child...");
    puts(foo);

//    sleep(1);
//    puts("Or maybe not ... :)");
//
//    if(kill(child, SIGKILL)){
//      puts("Killing child unsuccessfull :|");
//    } else {
//      puts("Killing child successfull :>");
//    }

    if(wait(&status) == child){
      printf("Child ended - status code: %d\n", WEXITSTATUS(status));
    }
  }

  return 0;
}

