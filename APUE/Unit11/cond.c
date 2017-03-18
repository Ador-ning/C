#include "../include/apue.h"
#include <pthread.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
/*######################################*/
/*
*	Interfaces
*/
void maketimeout(struct timespec *tsp, long minutes) {
  struct timeval now;

  /* get the current time */
  gettimeofday(&now, NULL);
  tsp->tv_sec = now.tv_sec;
  tsp->tv_nsec = now.tv_usec * 1000;
  tsp->tv_sec += minutes * 60;
}

struct msg {
  struct msg *m_next;
  /* can add more in here */
};

struct msg *workq;

pthread_cond_t qready = PTHREAD_COND_INITIALIZER;
pthread_mutex_t qlock = PTHREAD_MUTEX_INITIALIZER;

void process_msg(void) {
  struct msg *mp;
  for (;;) {
    pthread_mutex_lock(&qlock);

    while (workq == NULL) { /* waitting for queue have items */
      pthread_cond_wait(&qready, &qlock);
    }

    mp = workq;
    workq = mp->m_next;
    pthread_mutex_unlock(&qlock);

    /* processing *mp in here */
  }
}

void enqueue_msg(struct msg *mp) {
  pthread_mutex_lock(&qlock);
  mp->m_next = workq;
  workq = mp;
  pthread_mutex_unlock(&qlock);
  pthread_cond_signal(&qready);
}

int main(int argc, char const *argv[]) { return 0; }
