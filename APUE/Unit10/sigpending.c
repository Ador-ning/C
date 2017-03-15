#include "../include/apue.h"

/*########################################*/
static void sig_quit(int);

int main(int argc, char const *argv[]) {

  sigset_t new, old, pend;
  if (signal(SIGQUIT, sig_quit) == SIG_ERR) {
    err_sys("can't catch SIGINT");
  }

  /*
  *	Block SIGQUIT and save current signal mask
  */
  sigemptyset(&new);
  sigaddset(&new, SIGQUIT);

  if (sigprocmask(SIG_BLOCK, &new, &old) < 0) {
    err_sys("SIG_BLOCK error");
  } /* pending SIGQUIT */

  sleep(2);

  if (sigpending(&pend) < 0) {
    err_sys("sigpending error");
  }
  if (sigismember(&pend, SIGQUIT)) {
    printf("SIGQUIT pending");
  }

  if (sigprocmask(SIG_SETMASK, &old, NULL) < 0) {
    err_sys("SIG_SETMASK error"); /* unblocked SIGQUIT */
  }
  printf("SIGQUIT unblocked\n");

  sleep(2);

  return 0;
}

/*#########################################*/
static void sig_quit(int signo) {
  printf("catch SIGQUIT");
  if (signal(SIGQUIT, SIG_DFL) == SIG_ERR) {
    err_sys("can't reset SIGQUIT");
  }
}
