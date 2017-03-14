#include "../include/apue.h"

/*###########################################*/
static void sig_usr(int);

int main(int argc, char const *argv[]) {

  if (signal(SIGUSR1, sig_usr) == SIG_ERR) {
    err_sys("signal handling SIGUSR1 error");
  } else if (signal(SIGUSR2, sig_usr) == SIG_ERR) {
    err_sys("signal handling SIGUSR2 error");
  }

  for (;;) {
    pause();
  }
  return 0;
}

static void sig_usr(int signo) /* one signal handler for SIGUSR1 and SIGUSR2 */
{
  if (signo == SIGUSR1) {
    printf("Received SIGUSR1\n");
  } else if (signo == SIGUSR2) {
    printf("Received SIGUSR2\n");
  } else {
    err_sys("Received signal %d\n", signo);
  }
}
