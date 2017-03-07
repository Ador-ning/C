#include "apue.h"
#include <sys/signal.h>
/* signal realize it */
/*#############################*/
/* Local */
static volatile sig_atomic_t sig;
static sigset_t newmask, oldmask, zeromask;

static void
sig_usr(int signo) { /* one signal handler for SIGUSER1 and SIGUSER2 */
  sig = 1;
}

/*################################*/
void TELL_WAIT(void) {
  if (signal(SIGUSR1, sig_usr) == SIG_ERR) {
    err_sys("signal(SIGUSR1) error");
  }
  if (signal(SIGUSR2, sig_usr) == SIG_ERR) {
    err_sys("signal(SIGUSR2) error");
  }

  sigemptyset(&zeromask);
  sigemptyset(&newmask);
  sigaddset(&newmask, SIGUSR1);
  sigaddset(&newmask, SIGUSR2);

  /* Block SIGUSR1 and SIGUSR2, and save current signal masks */
  if (sigprocmask(SIG_BLOCK, &newmask, &oldmask) < 0) {
    err_sys("SIG_BLOCK error");
  }
}

void TELL_PARENT(pid_t pid) {
  /* tell parent we are done. */
  kill(pid, SIGUSR2);
}

void WAIT_PARENT(void) {
  while (sig == 0)
    sigsuspend(&zeromask);
  sig = 0;

  /* Reset signal mask to orignal mask. */
  if (sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0) {
    err_sys("SIG_SETMASK error");
  }
}

void TELL_CHILD(pid_t pid) {
  /* tell child we are done. */
  kill(pid, SIGUSR1);
}

void WAIT_CHILD(void) {
  while (sig == 0)
    sigsuspend(&zeromask);

  sig = 0;
  /* Reset signal mask to orignal mask. */
  if (sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0) {
    err_sys("SIG_SETMASK error");
  }
}
