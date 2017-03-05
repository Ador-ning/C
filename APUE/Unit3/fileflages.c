#include "../include/apue.h"
#include <fcntl.h>

int main(int argc, char const *argv[]) {
  /* code */
  int val;
  if (argc != 2)
    err_quit("usage: a.out <#descriptor#>");
  if ((val = fcntl(atoi(argv[1]), F_GETFL, 0)) < 0)
    err_sys("fcntl error for fd %d", atoi(argv[1]));

  switch (val & O_ACCMODE) {
  case O_RDONLY:
    printf("read only");
    break;
  case O_WRONLY:
    printf("write only");
    break;
  case O_RDWR:
    printf("read and write.");
    break;
  default:
    err_dump("unknown acceess mode.");
  }

  if (val & O_APPEND) {
    /* code */
    printf(", append.", );
  }

  if (val & O_NONBLOCK) {
    /* code */
    printf(", nonblock");
  }

  if (val & O_SYNC) {
    printf(", sync write.");
  }

#if !define(_POSIX_C_SOURCE) && define(O_FSYNC) && (O_FSYNC != O_SYNC)
  if (val & O_FSYNC) {
    /* code */
    printf(", sync writes.");
  }
#endif
  putchar('\n');
  return 0;
}
