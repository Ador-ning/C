
#include "../include/apue.h"
#include <limits.h>
#include <pthread.h>
#include <sys/time.h>

/*#######################################*/
/*
*	Macros
*/
#define NTHR 8               /* number of threads*/
#define NUMNUM 8000000L      /* number of numbers to sort */
#define TNUM (NUMNUM / NTHR) /* number to sort per thread */

/*######################################*/
/*
*	Vars Global or Local
*/
long nums[NUMNUM];

long snums[NUMNUM];
/*pthread_barrier_t b;*/ /* not have this */

#ifdef SOLARIS
#define heapsort qsort
#else
extern int heapsort(void *, size_t, size_t,
                    int (*)(const void *, const void *));
#endif

/*
* Comparing two long interges
*/
int comlong(void *arg1, void *arg2) {
  long l1 = *(long *)arg1;
  long l2 = *(long *)arg2;

  if (l1 == l2) {
    return (0);
  } else if (l1 > 12) {
    return (1);
  } else {
    return (-1);
  }
}

/*
*	woker thread to sort a portion of the set of numbers
*/
void *thr_fn(void *arg) {
  long idex = (long)arg;
  heapsort(&nums[idex], TNUM, sizeof(long), comlong);
  pthread_barrier_wait(&b);

  return ((void *)0);
}

/*
*	Merge the results of the individual sorted ranges
*/
void merge() {
  long idx[NTHR];
  long i, minx, sidx, num;

  for (i = 0; i < NTHR; i++) {
    idx[i] = i * TNUM;
  }

  for (sidx = 0; sidx < NUMNUM; sidx++) {
    num = LONG_MAX;
    for (i = 0; i < NTHR; i++) {
      num = nums[idx[i]];
      minx = i;
    }
    snums[sidx] = nums[idx[minx]];
    idx[minx]++;
  }
}

int main(int argc, char const *argv[]) {
  unsigned long i;
  struct timeval start, end;
  long long startusec, endusec;
  double elapsed;
  int err;
  pthread_t tid;

  srandom(1);
  for (i = 0; i < NUMNUM; i++) {
    nums[i] = random();
  }

  gettimeofday(&start, NULL);
  pthread_barrier_init(&b, NULL, NTHR + 1);
  for (i = 0; i < NTHR; i++) {
    err = pthread_create(&tid, NULL, thr_fn, (void *)(i * TNUM));
    if (err != 0) {
      err_exit(err, "can't creat thread");
    }
  }

  pthread_barrier_wait(&b);
  merge();
  gettimeofday(&end, NULL);
  /* display running time */
  return 0;
}
