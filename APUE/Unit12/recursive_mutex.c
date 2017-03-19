#include "../include/apue.h"
#include "./makethread.h"
#include <pthread.h>
#include <sys/time.h>
#include <time.h>

/*
*	Extern Global Static
*/
extern int makethread(void *(*)(void *), void *);

struct to_info {
  void (*to_fn)(void *); /* functions*/
  void *to_arg;          /* argument */
  struct timespec to_wait;
};

pthread_mutex_t mutex;
pthread_mutexattr_t attr;

/*
*	Macros
*/
#define SECTONSEC 1000000000 /* seconds to nanoseconds */

#if !defined(CLOCK_REALTIME) || defined(BSD)
#define clock_nanosleep(ID, FL, REQ, REM) nanpsleep((REQ), (REM))
#endif

#ifndef CLOCK_REALTIME
#define CLOCK_REALTIME 0
#define USECTONSEC 1000

/*
*	Functions
*/
void clock_gettime(int id, struct timespec *tsp) {
  struct timespec tv;

  gettimeofday(&tv, NULL);
  tsp->tv_sec = tv.tv_sec;
  tsp->tv_nsec = tv.tv_usec * USECTONSEC;
}
#endif

void *timeout_helper(void *arg) {
  struct to_info *tip;

  tip = (struct to_info *)arg;

  clock_nanosleep(CLOCK_REALTIME, 0, &tip->to_wait, NULL);
  (*tip->to_fn)(tip->to_arg);

  free(arg);
  return (void *)0;
}

void timeout(const struct timespec *when, void *(*func)(void *), void *arg) {
  struct timespec now;
  struct to_info *tip;
  int error;

  clock_gettime(CLOCK_REALTIME, &now);

  if ((when->tv_sec > now.tv_sec) ||
      (when->tv_sec == now.tv_sec && when->tv_nsec > now.tv_nsec)) {
    tip = malloc(sizeof(struct to_info));
    if (tip != NULL) {
      tip->to_fn = func;
      tip->to_arg = arg;
      tip->to_wait.tv_sec = when->tv_sec - now.tv_sec;
      if (when->tv_nsec >= now.tv_nsec) {
        tip->to_wait.tv_nsec = when->tv_nsec - now.tv_nsec;
      } else {
        tip->to_wait.tv_sec--; /* Borrow */
        tip->to_wait.tv_nsec = SECTONSEC - now.tv_nsec + when->tv_nsec;
      }

      error = makethread(timeout_helper,
                         (void *)tip); /* Detach state to creat thread */
      if (error == 0) {
        return; /* success */
      } else {
        free(tip); /* makethread fail */
        return;
      }
    } else {
      free(tip); /* malloc fails */
      return;
    }
  }
  /*
  *	when<=now
  */
  (*func)(arg);
}

void retry(void *argt) {
  pthread_mutex_lock(&mutex);
  /* perform retry steps */

  pthread_mutex_unlock(&mutex);
}

int main(int argc, char const *argv[]) {
  int error, arg;
  int condition = 0;
  struct timespec when;

  if ((error = pthread_mutexattr_init(&attr)) != 0) {
    err_exit(error, " pthread_mutexattr_init failed");
  }

  if ((error = pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE)) !=
      0) {
    err_exit(error, "can't set recursive type ");
  }

  if ((error = pthread_mutex_init(&mutex, &attr)) != 0) {
    err_exit(error, "can't init recursive mutex");
  }
  /* continue processing */

  pthread_mutex_lock(&mutex);

  /*
  *	Check condition under protection of a lock to make the check and the
  *call
  * to timeout atomic
  */
  if (condition) {
    clock_gettime(CLOCK_REALTIME, &when);
    when.tv_sec += 10;
    timeout(&when, retry, (void *)((unsigned long)arg));
  }
  pthread_mutex_unlock(&mutex);

  /*
  * Continue to processing
  */
  return 0;
}
