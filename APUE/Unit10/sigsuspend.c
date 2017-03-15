#include "../include/apue.h"

/*#######################################*/
static void sig_int(int);

int main(int argc, char const *argv[]) {
  sigset_t new, old, wait;

  pr_mask("starting main:");

  if (signal(SIGINT, sig_int) == SIG_ERR) {
    err_sys("signal(SIGINT) error");
  }

  sigemptyset(&wait);
  sigaddset(&wait, SIGUSR1);

  sigemptyset(&new);
  sigaddset(&new, SIGINT);

  /*
  *	Block SIGINT and Save current signal mask
  */
  if (sigprocmask(SIG_BLOCK, &new, &old) < 0) {
    err_sys("sigprocmask SIG_BLOCK error");
  }

  /*
  *	Critical region of code
  */
  pr_mask("in Critical region:");

  /*
  *	Pause, allowing all signal except SIGUSR1
  */
  if (sigsuspend(&wait) != -1) {
    err_sys("sigsuspend error");
  }

  pr_mask("after return from sigsuspend:");

  /*
  *	Reset signal, unblock SIGINT
  */
  if (sigprocmask(SIG_SETMASK, &old, NULL) < 0) {
    err_sys("SIG_SETMASK error");
  }

  pr_mask("main exitting:");
  return 0;
}

static void sig_int(int signo) { pr_mask("\nin sig_int:"); }
