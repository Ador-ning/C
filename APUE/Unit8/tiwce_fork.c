#include "../include/apue.h"
#include <sys/wait.h>

int main(int argc, char const *argv[]) {
  pid_t pid;

  if ((pid = fork()) < 0) {
    err_sys("error fork.");
  } else if (pid == 0) { /* First children */
    if ((pid = fork()) < 0) {
      err_sys("error fork.");
    } else if (pid > 0) { /* parent from second fork == first child */
      exit(0);
    }
    sleep(5); /* Let first child be killed -- exit(0) */
    printf("second child, parent pid = %ld\n",
           (long)getppid()); // Print the init processing ID
    exit(0);
  }

  if (waitpid(pid, NULL, 0) != pid) { /* wait for first child */
    err_sys("waitpid error.");
  }

  return 0;
}
