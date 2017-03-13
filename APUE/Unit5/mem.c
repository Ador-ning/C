#include "../include/apue.h"
#include <stdio.h>

#define BSZ 48

int main(int argc, char const *argv[]) {
  /* code */
  FILE *fp;
  static char buf[BSZ];

  memset(buf, 'a', BSZ - 2);
  buf[BSZ - 2] = '\0';
  buf[BSZ - 1] = 'X';
  /* fmemopen not support in MAC */
  if ((fp = fmemopen(buf, BSZ, "w+")) == NULL) {
    err_sys("fmemopen error.");
  }
  printf("initial buffer contents: %s\n", buf);
  fprintf(fp, "hello, unix.");
  printf("before fflush: %s\n", buf);
  fflush(fp);
  printf("after fflush: %s\n", buf);
  printf("len of string in buf = %ld\n", strlen(buf));

  memset(buf, 'b', BSZ - 2);
  buf[BSZ - 2] = '\0';

  return 0;
}
