#include "../include/apue.h"
#include "./daemon_single.h"
#include "./daemonize.h"
#include <errno.h>
#include <pthread.h>
#include <syslog.h>

sigset_t mask;

extern int already_running(void);
extern void daemonize(const char *);

void reread(void) { /**/
}

void *thr_fn(void *arg) {
  int error, signo;

  for (;;) {
    err = sigwait(&mask, &signo);
    if (err != 0) {
      syslog(LOG_ERR, "sigwait error");
      exit(1);
    }
  }

  switch (signo) {
  case SIGHUP:
    syslog(LOG_INFO, "Re-reading configuration file");
    reread();
    break;

  case SIGTERM:
    syslog(LOG_INFO, "got SIGTERM; exiting");
    exit(0);
  default:
    syslog(LOG_INFO, "unexpected signal %d\n", signo);
  }

  return ((void *)0);
}

int main(int argc, char const *argv[]) {
  int error;
  pthread_t tid;
  char *cmd;
  struct sigaction sa;

  if ((cmd = strrchr(argv[0], '/')) == NULL) {
    cmd = argv[0];
  } else
    cmd++;

  /*
  *	Become a deamon
  */
  daemonize(cmd);

  /*
  *	Make sure only one copy of the daemon is running
  */
  if (already_running()) {
    syslog(LOG_ERR, "daemon already running");
    exit(1);
  }

  /*
  *	Restore SIGHUP default and block all signals
  */
  sa.sa_handler = thr_fn;
  sigemptyset(&sa.sa_mask);
  sa.sa_flags = 0;

  if (sigaction(SIGHUP, &sa, NULL) < 0) {
    err_quit("%s: can'g Restore SIGHUP default");
  }
  sigfillset(&mask);
  if ((error = pthread_sigmask(SIG_BLOCK, &mask, NULL)) != 0) {
    err_exit(err, " SIG_BLOCK error");
  }

  /*
  *	Creat a thread to handle SIGHUP SIGTERM
  */
  error = pthread_create(&tid, NULL, thr_fn, 0);

  if (error != 0) {
    err_exit(error, "can't creat thread");
  }

  return 0;
}
