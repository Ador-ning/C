/*###################################*/
#include "../include/apue.h"
#include <sys/wait.h>

void pr_exit(int status) {
  if (WIFEXITED(status)) {
    printf("normal termination , exit status = %d\n", WEXITSTATUS(status));
  } else if (WIFSIGNALED(status)) {
    printf("abnormal termination, signal number = %d\n", WTERMSIG(status));
  } else if (WIFSTOPPED(status)) {
    printf("child stopped, signal number = %d\n", WSTOPSIG(status));
  }

#ifdef WCOREDUMP
  WCOREDUMP(status) ? "(core file generated)" : " ";
#else
  (" ");
#endif
}

/*#######################################*/

static volatile sig_atomic_t sigflag; /* set nonzero by sig handler */
static sigset_t newmask, oldmask, zeromask;

static void sig_usr(int signo) /* one signal handler for SIGUSR1 and SIGUSR2 */
{
  sigflag = 1;
}

void TELL_WAIT(void) {
  if (signal(SIGUSR1, sig_usr) == SIG_ERR)
    err_sys("signal(SIGUSR1) error");
  if (signal(SIGUSR2, sig_usr) == SIG_ERR)
    err_sys("signal(SIGUSR2) error");
  sigemptyset(&zeromask);
  sigemptyset(&newmask);
  sigaddset(&newmask, SIGUSR1);
  sigaddset(&newmask, SIGUSR2);

  /* Block SIGUSR1 and SIGUSR2, and save current signal mask */
  if (sigprocmask(SIG_BLOCK, &newmask, &oldmask) < 0)
    err_sys("SIG_BLOCK error");
}

void TELL_PARENT(pid_t pid) { kill(pid, SIGUSR2); /* tell parent we're done */ }

void WAIT_PARENT(void) {
  while (sigflag == 0)
    sigsuspend(&zeromask); /* and wait for parent */
  sigflag = 0;

  /* Reset signal mask to original value */
  if (sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0)
    err_sys("SIG_SETMASK error");
}

void TELL_CHILD(pid_t pid) { kill(pid, SIGUSR1); /* tell child we're done */ }

void WAIT_CHILD(void) {
  while (sigflag == 0)
    sigsuspend(&zeromask); /* and wait for child */
  sigflag = 0;

  /* Reset signal mask to original value */
  if (sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0)
    err_sys("SIG_SETMASK error");
}

/*#########################################*/

/*
*	Not defined in apue.h
*/
int system(const char *cmdstring) { /* Version-- with no signal handing */
  pid_t pid;
  int status;

  if (cmdstring == NULL) {
    return (1);
  }

  if ((pid = fork()) < 0) {
    err_sys("fork error");
  } else if (pid == 0) { /* child */
    execl("/bin/sh", "sh", cmdstring, (char *)0);
    _exit(127); /* execl error */
  } else {      /* parent */
    while (waitpid(pid, &status, 0) < 0) {
      if (errno != EINTR) {
        status = -1;
        break;
      }
    }
  }
  return (status);
}

/*
*	Add signal processing
*/
int sigsystem(const char *cmdstring) { /* Version-- with no signal handing */
  pid_t pid;
  int status;

  struct sigaction ignore, saveintr, saveqiut;
  sigset_t chldmask, savemask;

  if (cmdstring == NULL) {
    return (1);
  }

  ignore.sa_handler = SIG_IGN;
  sigemptyset(&ignore.sa_mask);
  ignore.sa_flags = 0;

  if (sigaction(SIGINT, &ignore, &saveintr) < 0) {
    return (-1);
  }

  if (sigaction(SIGQUIT, &ignore, &saveqiut) < 0) {
    return (-1);
  }

  sigemptyset(&chldmask);
  sigaddset(&chldmask, SIGCHLD);
  if (sigprocmask(SIG_BLOCK, &chldmask, &savemask) < 0) {
    return (-1);
  }

  if ((pid = fork()) < 0) {
    status = -1;
    err_sys("fork error");
  } else if (pid == 0) { /* child */
                         /*
                         *	restore it
                         */
    sigaction(SIGINT, &saveintr, NULL);
    sigaction(SIGQUIT, &saveqiut, NULL);
    sigprocmask(SIG_SETMASK, &savemask, NULL);

    execl("/bin/sh", "sh", cmdstring, (char *)0);
    _exit(127); /* execl error */
  } else {      /* parent */
    while (waitpid(pid, &status, 0) < 0) {
      if (errno != EINTR) {
        status = -1;
        break;
      }
    }
  }

  /*
  *	restore it
  */
  if (sigaction(SIGINT, &saveintr, NULL) < 0) {
    return (-1);
  }

  if (sigaction(SIGQUIT, &saveqiut, NULL) < 0) {

    return (-1);
  }

  if (sigprocmask(SIG_SETMASK, &savemask, NULL) < 0) {
    return (-1);
  }

  return (status);
}
