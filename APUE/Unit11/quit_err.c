#include "../include/apue.h"
#include <pthread.h>

struct foo {
  int a, b, c, d;
};

static void prinfoo(const char *s, const struct foo *fp) {
  printf("%s ", s);
  printf("structure at 0x%lx\n", (unsigned long)fp);
  printf("foo.a = %d\n", fp->a);
  printf("foo.b = %d\n", fp->b);
  printf("foo.c = %d\n", fp->c);
  printf("foo.d = %d\n", fp->d);
}

static void *thr_fn1(void *arg) {
  struct foo foo1 = {1, 2, 3, 4};
  prinfoo("thread1:\n", &foo1);
  return ((void *)&foo1);
}

static void *thr_fn2(void *arg) {
  printf("thread2: ID %lu\n", (unsigned long)pthread_self());
  pthread_exit((void *)2);
}

int main(int argc, char const *argv[]) {
  int error;
  pthread_t tid2, tid1;
  struct foo *fp;

  error = pthread_create(&tid1, NULL, thr_fn1, NULL);
  if (error != 0) {
    err_exit(error, "creat thread1 error");
  }
  error = pthread_join(tid1, (void *)&fp);
  if (error != 0) {
    err_exit(error, "can't join thread1");
  }

  sleep(1);
  printf("starting thread2\n");

  error = pthread_create(&tid2, NULL, thr_fn2, NULL);
  if (error != 0) {
    err_exit(error, "creat thread2 error");
  }
  sleep(1);
  prinfoo("parent:\n", fp);

  return 0;
}
