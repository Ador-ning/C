#include "../include/apue.h"
#include <pthread.h>

pthread_mutex_t lock1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t lock2 = PTHREAD_MUTEX_INITIALIZER;

void prepare(void) {
  int err;
  printf("preparing locks ...\n");

  if ((err = pthread_mutex_lock(&lcok1)) != 0) {
    err_cont(err, "can't lock lock1 in prepare handler");
  }

  if ((err = pthread_mutex_lock(&lcok2)) != 0) {
    err_cont(err, "can't lock lock2 in prepare handler");
  }
}

void parent(void) {
  int err;
  printf("parent unlocks ...\n");

  if ((err = pthread_mutex_lock(&lcok1)) != 0) {
    err_cont(err, "can't unlock lock1 in parent handler");
  }

  if ((err = pthread_mutex_lock(&lcok2)) != 0) {
    err_cont(err, "can't unlock lock2 in parent handler");
  }
}

void child(void) {
  int err;
  printf("child unlocks ...\n");

  if ((err = pthread_mutex_lock(&lcok1)) != 0) {
    err_cont(err, "can't unlock lock1 in child handler");
  }

  if ((err = pthread_mutex_lock(&lcok2)) != 0) {
    err_cont(err, "can't unlock lock2 in child handler");
  }
}

void *thr_fn(void *arg) {
  printf("thread started...\n", );
  pause();
  return (void *)0;
}

int main(int argc, char const *argv[]) {
  int err;
  pthread_t tid;
  pid_t pid;

  if ((err = pthread_atfork(prepare, parent, child)) != 0) {
    err_exit(err, "can't install fork handlers");
  }

  if ((err=pthread_create(&tid, NULL, thr_fn, 0) !=0) {
    err_exit(err, "can't creat thread");
	}

	sleep(2);
	printf("parent about to fork...\n");

	if ((pid = fork()) <0 ) {
    err_quit("fork failed");
	}else if (pid == 0) {	/* child */
    printf("child returned from fork\n");
	}else {
    printf("parent returned from fork\n");
	}

  return 0;
}
