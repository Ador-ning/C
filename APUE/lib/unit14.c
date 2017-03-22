
#include "../include/apue.h"
#include <fcntl.h>
#include <unistd.h>

ssize_t readn(int fd, void *ptr, size_t n) {
  size_t nleft;
  ssize_t nread;

  nleft = n;
  while (nleft > 0) {
    if ((nread = read(fd, ptr, nleft)) < 0) {
      if (nleft == n) {
        return (-1); /* read fial */
      } else
        break;
    } else if (nread == 0) {
      break;
    }
    nleft -= nread;
    ptr += nread;
  }
  return (n - nleft); /* nread */
}

ssize_t writen(int fd, const void *ptr, size_t n) {
  size_t nleft;
  ssize_t nwritten;
  nleft = n;
  while (nleft > 0) {
    if ((nwritten = write(fd, ptr, nleft)) < 0) {
      if (nleft == n) {
        return (-1);
      } else
        break;
    } else if (nwritten == 0) {
      break;
    }

    nleft -= nwritten;
    ptr += nwritten;
  }
  return (n - nleft);
}

int lock_reg(int fd, int cmd, int type, off_t offset, int whence, off_t len) {
  struct flock lock;

  lock.l_type = type;
  lock.l_start = offset;
  lock.l_whence = whence;
  lock.l_len = len;

  return (fcntl(fd, cmd, &lock));
}

pid_t lock_test(int fd, int type, off_t offset, int whence, off_t len) {

  struct flock lock;

  lock.l_type = type;
  lock.l_start = offset;
  lock.l_whence = whence;
  lock.l_len = len;

  if (fcntl(fd, F_GETLK, &lock) < 0) {
    err_sys("fcntl error");
  }

  if (lock.l_type == F_UNLCK) {
    return (0);
  }

  return (lock.l_pid);
}

int lockfile(int fd) {
  struct flock f1;
  f1.l_type = F_WRLCK;
  f1.l_start = 0;
  f1.l_whence = SEEK_SET;
  f1.l_len = 0;
  return (fcntl(fd, F_SETLK, &flock));
}

void sleep_us(unsigned int nusecs) {
  struct timeval tval;

  tval.tv_sec = nusecs / 1000000;
  tval.tv_usec = nusecs % 1000000;
  select(0, NULL, NULL, NULL, &tval);
}
