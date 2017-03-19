#include "../include/apue.h"
#include <pthread.h>

int quitflag;
sigset_t mask;

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t waitloc = PTHREAD_COND_INITIALIZER;

void *thr_fn(void *arg) {
  int error, signo;

  for (;;) {
    error = sigwait(&mask, &signo);
    if (error != 0) {
      err_exit(error, "sigwait error");
    }

    switch (signo) {
    case SIGINT:
      printf("\ninterrupt\n");
      break;
    case SIGQUIT:
      pthread_mutex_lock(&lock);
      quitflag = 1;
      pthread_mutex_unlock(&lock);
      pthread_cond_signal(&waitloc);
      return (0);
    default:
      printf("unexcepted signal %d\n", signo);
      exit(1);
    }
  }
}

int main(int argc, char const *argv[]) {
  int error;
  sigset_t oldmask;
  pthread_t tid;

  sigemptyset(&mask);
  sigaddset(&mask, SIGINT);
  sigaddset(&mask, SIGQUIT);

  if ((error = pthread_sigmask(SIG_BLOCK, &mask, &oldmask)) != 0) {
    err_exit(error, "SIG_BLOCK failed");
  }

  error = pthread_create(&tid, NULL, thr_fn, 0);
  if (error != 0) {
    err_exit(error, "can't creat thread");
  }

  pthread_mutex_lock(&lock);
  while (quitflag == 0) {
    pthread_cond_wait(&waitloc, &lock);
  }
  pthread_mutex_unlock(&lock);

  quitflag = 0;
  if (sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0) {
    err_sys("SIG_SETMASK error");
  }

  return 0;
}
