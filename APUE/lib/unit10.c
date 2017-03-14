#include "../include/apue.h"
#include <setjmp.h>
#include <signal.h>
#include <unistd.h>
/*#############################################*/
/*
*	Sleep1
*/
static void sig_alrm1(int signo) { /*nothing to do*/
}

unsigned int sleep1(unsigned int seconds) {
  if (signal(SIGALRM, sig_alrm1) == SIG_ERR) {
    err_sys("SIGALRM processing error");
    return (seconds);
  }
  alarm(seconds);
  pause();
  return (alarm(0)); /* trun off timer */
}

/*#############################################*/
/*
*	Sleep2
*/
static jmp_buf buf;

static void sig_alrm2(int signo) { /*nothing to do*/
  longjmp(buf, 1);
}

unsigned int sleep2(unsigned int seconds) {
  if (signal(SIGALRM, sig_alrm2) == SIG_ERR) {
    err_sys("SIGALRM processing error");
    return (seconds);
  }

  if (setjmp(buf) == 0) { /* longjmp successing return */
    alarm(seconds);
    pause();
  }
  return (alarm(0)); /* trun off timer */
}
