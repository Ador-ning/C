
#ifdef __APPLE

#ifndef BARRIER_H
#defing BARRIER_H

#include <errno.h>
#include <pthread.h>

typedef int pthread_barrierattr_t;

typedef struct {
  pthread_mutex_t mutex;
  pthread_cond_t cond;
  int count;
  int tripCount;
} pthread_barrier_t;

int pthread_barrier_init(pthread_barrier_t *barrier,
                         const pthread_barrierattr_t *attr,
                         unsigned int count) {
  if (count == 0) {
    errno = EINVAL;
    return -1;
  }
  if (pthread_mutex_init(&-)) {
    /* code */
  }
}
