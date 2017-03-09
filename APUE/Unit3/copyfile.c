#include "../include/apue.h"

int main(int argc, char const *argv[]) {
  /* code */
  int n;
  char buf[MAXLINE / 4];
  while ((n = read(STDIN_FILENO, buf, MAXLINE / 4)) > 0)
    if (write(STDOUT_FILENO, buf, n) != n)
      err_sys("write error.");

  if (n < 0)
    err_sys("read error.");
  return 0;
}

/*
*	More intellgence to need modify
**/
