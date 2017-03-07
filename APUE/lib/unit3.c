#include "apue.h"
#include <fcntl.h>

void set_fl(int fd, int falgs) {
  int val;
  if ((val = fcntl(fd, F_GETFL, 0)) < 0) {
    err_sys("fcntl F_GETFL error.");
  }
  val |= falgs;
  if (fcntl(fd, F_SETFL, val) < 0)
    err_sys("fcntl F_SETFL error.");
}

void clr_fl(int fd, int falgs) {
  int val;
  if ((val = fcntl(fd, F_GETFL, 0)) < 0) {
    /* code */
    err_sys("fcntl F_GETFL error.");
  }
  val &= ~falgs;
  if (fcntl(fd, F_SETFL, val) < 0)
    err_sys("fcntl F_SETFL error.");
}
