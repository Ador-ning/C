#include "../include/apue.h"
#include <pthread.h>
#include <stdlib.h>

/* define in *.c  and extern struct foo; */
struct foo {
  int f_count;
  pthread_mutex_t f_lock;
  int f_id;
  /* more stuff can be added in here */
};

/*################################*/
/*
*	Interfaces
*/
struct foo *foo_alloc(int id) {
  struct foo *f;

  if ((f = malloc(sizeof(struct foo))) != NULL) {
    f->f_count = 1;
    f->f_id = id;

    if (pthread_mutex_init(&f->f_lock, NULL) != 0) {
      free(f); /* malloc failed */
      return ((struct foo *)NULL);
    }
  } /* initialization */

  return (f);
}

void foo_hold(struct foo *f) {
  pthread_mutex_lock(&f->f_lock);
  f->f_count++;
  pthread_mutex_unlock(&f->f_lock);
}

void foo_rele(struct foo *f) {
  pthread_mutex_lock(&f->f_lock);
  if ((--f->f_count) == 0) {
    pthread_mutex_unlock(&f->f_lock);
    pthread_mutex_destroy(&f->f_lock);
    free(f);
  } else {
    pthread_mutex_unlock(&f->f_lock);
  }
}
