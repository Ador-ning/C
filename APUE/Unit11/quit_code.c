#include "../include/apue.h"
#include <pthread.h>

static void *thr_fn1(void *arg) {
  sleep(2);
  printf("thread1 returning \n");
  return ((void *)1);
}

static void *thr_fn2(void *arg) {
  printf("thread2 running \n");
  pthread_exit((void *)2);
}

int main(int argc, char const *argv[]) {
  pthread_t tid1, tid2;
  int error;

  void *tret;

  error = pthread_create(&tid1, NULL, thr_fn1, NULL);
  if (error != 0) {
    err_exit(error, "can't creat thread1");
  }

  error = pthread_create(&tid2, NULL, thr_fn2, NULL);
  if (error != 0) {
    err_exit(error, "can't creat thread2");
  }

  /*
  *	the questions of tret using at two threds and the runing threads
  *precedences
  */
  error = pthread_join(tid1, &tret);
  if (error != 0) {
    err_exit(error, "can't join thread1");
  }
  printf("thread1 exiting code: %d\n", (int)tret);

  error = pthread_join(tid2, &tret);
  if (error != 0) {
    err_exit(error, "can't join thread2");
  }
  printf("thread2 exiting code: %d\n", (int)tret);

  return 0;
}
