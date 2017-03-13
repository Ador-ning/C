#include "../include/apue.h"
#include <errno.h>
#include <sys/time.h>

#ifdef MACOS
#include <sys/syslimits.h>
#endif

#ifdef SOLARIS
#include <limits.h>
#endif

#ifdef BSD
#include <sys/param.h>
#endif

unsigned long long count;
struct timeval time1;

/*#######################################*/
void checktime(char *str) {
  struct timeval va;
  gettimeofday(&va, NULL);
  if (va.tv_sec > time1.tv_sec && va.tv_usec > time1.tv_usec) {
    printf("%s count = %lld\n", str, count);
    exit(0);
  }
}

int main(int argc, char const *argv[]) {
  pid_t pid;
  char *s;
  int nzero = 20;
  int ret;
  int adj = 0;

  setbuf(stdout, NULL); /* unbuffered */

  if (argc == 2) {
    adj = strtol(argv[1], NULL, 10);
  }

  gettimeofday(&time1, NULL);
  time1.tv_sec += 10;

  if ((pid = fork()) < 0) {
    err_sys("fork error");
  } else if (pid == 0) {
    s = "child";
    printf("current nice value in child is %d, adjusting by %d\n",
           nice(0) + nzero, adj);
    errno = 0;
    if ((ret = nice(adj)) == -1 && errno != 0) {
      err_sys("child set scheduling priority");
    }
    printf("now child nice value in parent is %d\n", nice(0) + nzero);
  } else {
    s = "parent";
    printf(" current nice value in parent is %d\n", nice(0) + nzero);
  }

  for (;;) {
    if (++count == 0) {
      err_quit("%s counter wrap", s);
    }
    checktime(s);
  }

  return 0;
}
