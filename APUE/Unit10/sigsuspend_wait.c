#include "../include/apue.h"

/*##################################*/
static volatile sig_atomic_t quitflag;

static void sig_int(int signo) {
  if (signo == SIGINT) {
    printf("\ninterrupt\n");
  } else if (signo == SIGQUIT) {
    quitflag = 1;
  }
}

int main(int argc, char const *argv[]) {
  sigset_t old, new, zero;
  if (signal(SIGINT, sig_int) == SIG_ERR) {
    err_sys("signal - SIGINT error");
  }

  if (signal(SIGQUIT, sig_int) == SIG_ERR) {
    err_sys("signal - SIGQUIT error");
  }
  sigemptyset(&zero);
  sigemptyset(&new);
  sigaddset(&new, SIGQUIT);
  sigaddset(&zero, SIGINT); /*Ignore SIGINT*/

  /*
  *	Block SIGINT adn Save
  */
  if (sigprocmask(SIG_BLOCK, &new, &old) < 0) {
    err_sys("Block error");
  }

  while (quitflag == 0) {
    sigsuspend(&zero); /* zero is NULL */
  }

  quitflag = 0;

  if (sigprocmask(SIG_SETMASK, &old, NULL) < 0) {
    err_sys("SIG_SETMASK error");
  }

  return 0;
}
