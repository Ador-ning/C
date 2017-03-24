#include "../include/apue.h"
#include "../include/slock.h"
#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/wait.h>
/*######################################*/
/*
*	Using Pipe to realize it
*/
static int pfd1[2], pfd2[2];

void TELL_WAIT_P(void) {
  if (pipe(pfd1) < 0 || pipe(pfd2) < 0) {
    err_sys("pipe error");
  }
}

void TELL_PARENT_P(pid_t pid) { /* child */
  if (write(pfd2[1], "c", 1) != 1) {
    err_sys("write error");
  }
}

void TELL_CHILD_P(pid_t pid) { /* parent */
  if (write(pfd1[1], "p", 1) != 1) {
    err_sys("write error");
  }
}

void WAIT_PARENT_P(void) { /* child */
  char c;
  if (read(pfd1[0], &c, 1) != 1) {
    err_sys("read error");
  }

  if (c != 'p') {
    err_quit("WAIT_PARENT_P: incorrect data");
  }
}

void WAIT_CHILD_P(void) { /* child */
  char c;
  if (read(pfd2[0], &c, 1) != 1) {
    err_sys("read error");
  }

  if (c != 'c') {
    err_quit("WAIT_CHILD_P: incorrect data");
  }
}
/*######################################*/
static pid_t *childpid = NULL;

static int maxfd;

FILE *popen(const char *cmdstring, const char *type) {
  int i;
  int pfd[2];
  pid_t pid;

  FILE *fp;

  /*allow "r" or "w"*/
  if ((type[0] != 'r' && type[0] != 'w') || type[1] != 0) {
    errno = EINVAL;
    return NULL;
  }

  /* childpid[] */
  if (childpid == NULL) {
    maxfd = open_max();
    if ((childpid = calloc(maxfd, sizeof(pid_t))) == NULL)
      return NULL;
  }

  /* pipe check */
  if (pipe(pfd) < 0) {
    return NULL;
  }
  if (pfd[0] >= maxfd || pfd[1] >= maxfd) {
    close(pfd[0]);
    close(pfd[1]);
    errno = EMFILE;
    return NULL;
  }

  if ((pid = fork()) < 0) {
    return NULL;
  } else if (pid == 0) { /* child */
    if (*type == 'r') {
      close(pfd[0]);
      if (pfd[1] != STDOUT_FILENO) {
        dup2(pfd[1], STDOUT_FILENO);
        close(pfd[1]);
      }
    } else {
      close(pfd[1]);
      if (pfd[0] != STDIN_FILENO) {
        dup2(pfd[0], STDIN_FILENO);
        close(pfd[0]);
      }
    }

    /* close all descruptors in childpid[] */
    for (i = 0; i < maxfd; i++) {
      if (childpid[i] > 0) {
        close(i);
      }
    }

    execl("/bin/sh", "sh", "-c", cmdstring, (char *)0);
    _exit(127);
  }

  /* parent continue */
  if (*type == 'r') {
    close(pfd[1]);
    if ((fp = fdopen(pfd[0], type)) == NULL) {
      return NULL;
    }
  } else {
    close(pfd[0]);
    if ((fp = fdopen(pfd[1], type)) == NULL) {
      return NULL;
    }
  }

  childpid[fileno(fp)] = pid; /* remember child pid for this fd */
  return (fp);
}

int pclose(FILE *fp) {
  int fd, stat;
  pid_t pid;

  if (childpid == NULL) {
    errno = EINVAL;
    return (-1);
  }

  fd = fileno(fp);
  if (fd >= maxfd) {
    errno = EINVAL;
    return (-1);
  }

  if ((pid = childpid[fd]) == 0) {
    errno = EINVAL;
    return (-1);
  }

  childpid[fd] = 0;
  if (fclose(fp) == EOF) {
    return (-1);
  }

  return (stat);
}
/*######################################*/
struct slock *s_alloc() {
  struct slock *sp;
  static int cnt;

  if ((sp = malloc(sizeof(struct slock))) == NULL) {
    return (NULL);
  }

  do {
    snprintf(sp->name, sizeof(sp->name), "/%ld.%d", (long)getpid(), cnt++);
    sp->semp = sem_open(sp->name, O_CREAT | O_EXCL, S_IRWXU, 1);
  } while ((sp->semp == SEM_FAILED) && (errno = EEXIST));

  if (sp->semp == SEM_FAILED) {
    free(sp);
    return (NULL);
  }
  sem_unlink(sp->name);
  return (sp);
}

void s_free(struct slock *sp) {
  sem_close(sp->semp);
  free(sp);
}

int s_lock(struct slock *sp) { return (sem_wait(sp->semp)); }

int s_strylock(struct slock *sp) { return (sem_trywait(sp->semp)); }

int s_unlock(struct slock *sp) { return (sem_post(sp->semp)); }
/*######################################*/
