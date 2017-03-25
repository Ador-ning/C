#include "../include/apue.h"
#include <sys/wait.h>

/*##########################################*/
static void sig_cld(int);

int main(int argc, char const *argv[]) {
  pid_t pid;

  if (signal(SIGCHLD, sig_cld) == SIG_ERR) {
    perror("Signal error");
  } /* shared */

  if ((pid = fork()) < 0) {
    err_sys("fork error");
  } else if (pid == 0) { /* child */
    sleep(2);
    printf("child pid = %d\n", getpid());
    _exit(0);
  } else {

    pause(); /* parent */

    exit(0);
  }
}

static void sig_cld(int signo) {
  pid_t pid;
  int status;

  printf("SIGCHLD Received\n");

  if ((pid = wait(&status)) < 0) { /* fetch child status */
    perror("wait error");
  }
  printf("pid = %d, ppid = %d\n", getpid(), getppid());
}
