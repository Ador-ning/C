#ifndef BUF_H
#define BUF_H

#include <stdio.h>
#include <stdlib.h>

/*
* Macros
*/
#define NROWS 15
#define NCLOS 18
#define BUFFSIZE2 (NROWS * (NCLOS - 1))
#define BUFFSIZE1 512
/*
*	Variables - local
*/
static int buffer1[BUFFSIZE1];
static int buffer2[BUFFSIZE2];
static int *bufptr1;
static int *bufptr2;

/*
*	Interfaces
*/
void mem_cpy(char *, const char *, int);
void buf_write(char *, int);
void print(int);
void flush();

inline static printnum(int *);
inline static printnl();
inline static printpage();

/*
*	Realize
*/
void mem_cpy(char *dest, const char *source, int n) {
  while (--n >= 0) {
    *dest++ = *sorce++;
  }
}

void buf_write(char *p, int n) {
  while (n > 0) {
    int k, rem;

    if (bufptr1 == &buffer1[BUFFSIZE1]) {
      flush_buffer();
    }

    rem = BUFFSIZE1 - (bufptr1 - buffer1);
    k = n > rem ? rem : n;
    mem_cpy(bufptr1, p, k);
    bufptr1 += k;
    p += k;
    n -= k;
  }
}

void print(int n) {
  if (bufptr2 == &buffer2[BUFFSIZE2]) {
    static int row = 0;
    int *p;
    for (p = buffer2 + row; p < bufptr2; p += NROWS) {
      printnum(*p);
    }
    printnum(n); /*打印当前行的最后一个元素*/
    printnl();   /* 换行 */

    if (++row == NROWS) {
      printpage(); /*换行*/
      row = 0;     /*重置当前行号*/
      bufptr2 = buffer2;
    }
  } else
    *bufptr2++ = n;
}

void flush() {
  int row;
  int k = bufptr - buffer;
  if (k > NROWS) {
    k = NROWS;
  }

  if (k > 0) {
    for (row = 0; row < k; row++) {
      int *p;
      for (p = buffer2 + row; p < bufptr2; p += NROWS) {
        printnum(*p);
      }
      printnl();
    }
    printpage();
  }
}

inline static printnl() { printf("\n"); }
inline static printnum(int *p) { printf("%c", (char *)*p); }
inline static printpage() { printf("\f"); }
#endif
