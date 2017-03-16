#include "../include/apue.h"
#include <pthread.h>

static void cleanup(void *arg) { printf("cleanup: %s\n", (char *)arg); }

static void *thr_fn1(void *arg) {
  printf("thread1 \n");
  pthread_cleanup_push(cleanup, "thread1 first hanler");
  pthread_cleanup_push(cleanup, "thread1 second hanler");
  printf("thread1 push complete\n");
  if (arg) {
    return ((void *)1);
  }
  pthread_cleanup_pop(1);
  pthread_cleanup_pop(1);
  return ((void *)1);
}

static void *thr_fn2(void *arg) {
  printf("thread2 \n");
  pthread_cleanup_push(cleanup, "thread2 first hanler");
  pthread_cleanup_push(cleanup, "thread2 second hanler");
  printf("thread2 push complete\n");
  if (arg) {
    pthread_exit((void *)2);
  }
  pthread_cleanup_pop(2);
  pthread_cleanup_pop(2);
  pthread_exit((void *)2);
}

int main(int argc, char const *argv[]) {
  int error;
  static pthread_t tid1, tid2;
  void *tret;

  error = pthread_create(&tid1, NULL, thr_fn1, (void *)1);
  if (error != 0) {
    err_exit(error, "error creat thread1");
  }
  error = pthread_create(&tid2, NULL, thr_fn2, (void *)1);
  if (error != 0) {
    err_exit(error, "error creat thread2");
  }

  error = pthread_join(tid1, &tret);
  if (error != 0) {
    err_exit(error, "can't jion thread1");
  }
  printf("thread1 exit code %ld\n", (long)tret);

  error = pthread_join(tid2, &tret);
  if (error != 0) {
    err_exit(error, "can't jion thread2");
  }
  printf("thread2 exit code %ld\n", (long)tret);

  return 0;
}
