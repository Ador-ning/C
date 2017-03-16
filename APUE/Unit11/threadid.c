#include "../include/apue.h"
#include <pthread.h>
pthread_t thd;

static void printids(const char *s) {
  pid_t pid;
  pthread_t tid;

  pid = getpid();
  tid = pthread_self();
  printf("%s pid:%lu tid :%lu (0x%lu)\n", s, (unsigned long)pid,
         (unsigned long)tid, (unsigned long)tid);
}

static void *thr_fn(void *arg) {
  printids("new thread: ");
  return ((void *)0);
}

int main(int argc, char const *argv[]) {
  int error;
  error = pthread_create(&thd, NULL, thr_fn, NULL);

  if (error != 0) {
    err_exit(error, "can't creat thread");
  }
  sleep(3);
  printids("main thread: ");

  return 0;
}
