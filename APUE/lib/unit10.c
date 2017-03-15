#include "../include/apue.h"
#include <errno.h>
#include <setjmp.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/signal.h>
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

/*###############################################*/

/*
*	Macros
*/
#define SIGBAD(signo) ((signo) <= 0 || (signo) >= NSIG)

int mysigaddset(sigset_t *sig, int signo) {
  if (SIGBAD(signo)) {
    err_sys("signo error");
    errno = EINVAL;
    return (-1);
  }

  *sig |= 1 << (signo - 1);
  return (0);
}

int mysigdelset(sigset_t *sig, int signo) {
  if (SIGBAD(signo)) {
    err_sys("signo error");
    errno = EINVAL;
    return (-1);
  }

  *sig &= ~(1 << (signo - 1));
  return (0);
}

int mysigismember(const sigset_t *sig, int signo) {
  if (SIGBAD(signo)) {
    err_sys("signo error");
    errno = EINVAL;
    return (-1);
  }

  return ((*sig & (1 << (signo - 1))) != 0);
}

/*######################################*/
/*
*	Signle Thread Version
*/
void pr_mask(const char *str) {
  sigset_t set;
  int errno_save;

  errno_save = errno;

  if (sigprocmask(0, NULL, &set) < 0) {
    err_ret("sigprocmask error");
  } else {
    printf("%s", str);
    if (mysigismember(&set, SIGINT)) {
      printf("SIGINT ");
    }

    if (mysigismember(&set, SIGQUIT)) {
      printf("SIGQUIT ");
    }

    if (mysigismember(&set, SIGUSR1)) {
      printf("SIGUSR1 ");
    }

    if (mysigismember(&set, SIGUSR2)) {
      printf("SIGUSR2 ");
    }

    if (mysigismember(&set, SIGALRM)) {
      printf("SIGALRM ");
    }
    /* go on to writting others test Set */
    printf("\n");
  }

  errno = errno_save;
}

/*#################################################*/

/* typedef void Sigfunc(int) */
Sigfunc *signal_intr(int signo, Sigfunc *func) {
  struct sigaction act, oact;
  act.sa_handler = func;
  sigemptyset(&act.sa_mask);
  act.sa_flags = 0;
#ifdef SA_INTERRUPT
  act.sa_flags |= SA_INTERRUPT;
#endif
  if (sigaction(signo, &act, &oact) < 0) {
    return (SIG_ERR);
  }
  return (oact.sa_handler);
}

Sigfunc *mysignal(int signo, Sigfunc *func) {
  struct sigaction act, oact;
  act.sa_handler = func;
  sigemptyset(&act.sa_mask);
  act.sa_flags = 0;

  if (signo == SIGALRM) {
#ifdef INTERRUPT
    act.sa_flags |= SA_INTERRUPT;
#endif
  } else {
    act.sa_flags |= SA_RESTART;
  }
  if (sigaction(signo, &act, &oact) < 0) {
    err_sys("sigaction error");
    return (SIG_ERR);
  }

  return (oact.sa_handler);
}

/*#######################################*/
void myabort(void) {
  sigset_t mask;
  struct sigaction action;

  sigaction(SIGABRT, NULL, &action);
  if (action.sa_handler == SIG_IGN) {
    action.sa_handler = SIG_DFL;
    sigaction(SIGABRT, &action, NULL);
  } else if (action.sa_handler == SIG_DFL) {
    fflush(NULL);
  }

  sigfillset(&mask);
  sigdelset(&mask, SIGABRT);
  sigprocmask(SIG_SETMASK, &mask, NULL);
  kill(getpid(), SIGABRT); /* send the signal */

  fflush(NULL);
  action.sa_handler = SIG_DFL;
  sigaction(SIGABRT, &action, NULL);
  sigprocmask(SIG_SETMASK, &mask, NULL);
  kill(getpid(), SIGABRT);
  exit(1);
}
