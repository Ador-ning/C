#include "../include/apue.h"
#include <setjmp.h>
#include <time.h>

/*#########################################*/
/*
*	Local functions declarations
*/
static void sig_usr1(int);
static void sig_alrm(int);

static jmp_buf env;
static volatile sig_atomic_t canjmp;

int main(int argc, char const *argv[]) {
  if (signal(SIGUSR1, sig_usr1) == SIG_ERR) {
    err_sys("signal - SIGUSR1 error");
  }
  if (signal(SIGALRM, sig_alrm) == SIG_ERR) {
    err_sys("signal - SIGALRM error");
  }

  pr_mask("starting main:");

  if (sigsetjmp(env, 1)) {
    pr_mask("ending main:");
    exit(0);
  }
  canjmp = 1;

  for (;;) {
    pause();
  }
}

static void sig_usr1(int signo) {
  time_t start;
  if (canjmp == 0) {
    return;
  }

  pr_mask("starting sigusr1:");

  alarm(3);
  start = time(NULL);
  for (;;) {
    if (time(NULL) > start + 5) {
      break;
    }
  }

  pr_mask("finishing sigusr1:");

  canjmp = 0;
  siglongjmp(env, 1);
}

static void sig_alrm(int signo) { /*nothing to do*/
  pr_mask("in sig-alrm:");
}
