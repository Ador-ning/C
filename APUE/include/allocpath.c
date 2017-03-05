#include "../include/apue.h"
#include <limits.h>

#ifdef PATH_MAX
staic long pathmax = PATH_MAX;
#else
statc long pathmax = 0;
#endif

#define PATHMAX_GUESS 512

static long posix_version = 0;
static long xsi_version = 0;

char *path_alloc(size_t *sizep) {
  char *ptr;
  size_t n;
  if (posix_version == 0)
    posix_version = sysconf(_SC_VERSION);

  if (xsi_version == 0)
    xsi_version = sysconf(_SC_XOPEN_VERSION);

  if (pathmax == 0) {
    errno = 0;
    if ((pathmax = pathconf("/", _PC_PATH_MAX)) < 0) {
      if (errno == 0)
        pathmax = PATHMAX_GUESS;
      else
        err_sys("pathconf error for _PC_PATH_MAX");
    } else {
      pathmax++;
    }
  }

  /* malloce */
  if ((posix_version < 200112L) && (xsi_version < 4))
    n = pathmax + 1;
  else
    n = pathmax;

  if ((ptr = malloc(n)) == NULL)
    err_sys("malloc error for pathname.");
  if (sizep != NULL)
    *sizep = n;
  return ptr;
}
