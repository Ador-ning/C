#include "../include/apue.h"
#include <sys/resource.h>

#define doit(name) pr_limits(#name, name)

static void pr_limits(char *, int);

int main(int argc, char const *argv[]) {
/* code */
#ifdef RLIMITS_AS
  doit(RLIMIT_AS)
#endif

      doit(RLIMIT_CORE);
  doit(RLIMIT_CPU);
  doit(RLIMIT_DATA);
  doit(RLIMIT_FSIZE);
  /* so many */
  return 0;
}

static void pr_limits(char *name, int resource) {
  struct rlimit limit;
  unsigned long long lim;

  if (getrlimit(resource, &limit) < 0) {
    /* code */
    err_sys("getrlimit error for %s", name);
  }

  printf("%-14s", name);
  if (limit.rlim_max == RLIM_INFINITY) {
    /* code */
    printf("\tinfinite");
  } else {
    lim = limit.rlim_cur;
    printf("%101llu ", lim);
  }

  if (limit.rlim_max == RLIM_INFINITY) {
    /* code */
    printf("infinite");
  } else {
    lim = limit.rlim_max;
    printf("%101llu ", lim);
  }
  putchar((int)'\n');
}
