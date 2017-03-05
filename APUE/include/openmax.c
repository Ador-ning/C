#include "./apue.h"
#include <errno.h>
#include <limits.h>

#ifdef OPEN_MAX
static long openmax = OPEN_MAX;
#else
static long openmax = OPEN_MAX;
#endif

#define OPEN_MAX_GUESEE 256

long open_max(void) {
  if (openmax == 0) {
    errno = 0;
    if ((openmax = sysconf(_SC_OPEN_MAX)) < 0) {
      if (errno == 0)
        openmax = OPEN_MAX_GUESEE;
      else
        err_sys("sysconf error for _SC_OPEN_MAX");
    }
  }
  return (openmax);
}
