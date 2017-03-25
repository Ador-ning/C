#include "../include/apue.h"
#include <pthread.h>
#include <time.h>

int main(int argc, char const *argv[]) {
  struct timespec time1;
  struct tm *tmp; /* <time.h> */

  char buf[64];
  pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

  pthread_mutex_lock(&lock);
  printf("mutex is locked\n");
  clock_gettime(CLOCK_REALTIME, &time1);
  tmp = localtime(&time1.tv_sec);
  strftime(buf, sizeof(buf), "%r", tmp);
  printf("time :%s\n", buf);

  time1.tv_sec += 10;

  return 0;
}
