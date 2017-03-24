#ifndef SLOCK_H
#define SLOCK_H

#include "./apue.h"
#include <semaphore.h>

struct slock {
  sem_t *semp;
  char name[NAME_MAX];
};

/*
*	Interfaces
*/
struct slock *s_alloc();
void s_free(struct slock *sp);
int s_strylock(struct slock *sp);
int s_lock(struct slock *sp);
int s_unlock(struct slock *sp);
#endif
