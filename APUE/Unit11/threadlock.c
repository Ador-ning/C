#include "../include/apue.h"
#include <pthread.h>
#include <stdlib.h>

/*
*	Macros
*/
#define NHASH 29
#define HASH(id) (((int)id) % NHASH)

struct foo {
  int f_count;
  int f_id;
  pthread_mutex_t f_lock;
  struct foo *f_next;
  /* add more stuff */
};

struct foo *fh[NHASH];
pthread_mutex_t hashlock = PTHREAD_MUTEX_INITIALIZER;

/*###################################*/
/*
*	Local functions
*/
static struct foo *foo_alloc(id) {
  struct foo *fp;
  int idx;

  if ((fp = malloc(sizeof(struct foo))) != NULL) {
    fp->f_id = id;
    fp->f_count = 1;
    if (pthread_mutex_init(&fp->f_lock, NULL) != 0) {
      free(fp);
      return (NULL);
    }

    /*
    *	Insert into Hash table
    */
    idx = HASH(id);
    pthread_mutex_lock(&hashlock);
    fp->f_next = fh[idx]; /* Insert Position : the list head */
    fh[idx] = fp;
    pthread_mutex_lock(&fp->f_lock);
    pthread_mutex_unlock(&hashlock);

    /* continue initialization new fp */
    pthread_mutex_unlock(&fp->f_lock);
  }

  return fp;
}

static void foo_hold(struct foo *fp) {
  pthread_mutex_lock(&fp->f_lock);
  fp->f_count++;
  pthread_mutex_unlock(&fp->f_lock);
}

static struct foo *foo_find(int id) {
  struct foo *fp;

  pthread_mutex_lock(&hashlock);
  for (fp = fh[HASH(id)]; fp != NULL; fp = fp->f_next) {
    if (fp->f_id == id) {
      fp->f_count++;
      break;
    }
  }
  pthread_mutex_unlock(&hashlock);
  return (fp);
}

static void foo_rele(struct foo *fp) {
  struct foo *tfp;
  int idx;

  pthread_mutex_lock(&hashlock);
  if (--fp->f_count == 0) { /* lase reference, remove from list */
    idx = HASH(fp->f_id);
    tfp = fh[idx];
    if (tfp == fp) {
      fh[idx] = fp->f_next;
    } else {
      while (tfp->f_next != fp) {
        tfp = tfp->f_next;
      }
      tfp->f_next = fp->f_next;
    }
    /* remove */
    pthread_mutex_unlock(&hashlock);
    pthread_mutex_destroy(&fp->f_lock);
    free(fp);
  } else {
    pthread_mutex_unlock(&hashlock);
  }
}

int main(int argc, char const *argv[]) { return 0; }
