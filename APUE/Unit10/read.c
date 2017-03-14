#include "../include/apue.h"
#include <setjmp.h>

/*
*	Time Limiting Read
*/

/*#######################################*/
/*
*	Local
*/
static void sig_alrm(int);
static jmp_buf buf;

int main(int argc, char const *argv[]) {
  int n;
  char line[MAXLINE];

  if (signal(SIGALRM, sig_alrm) == SIG_ERR) {
    err_sys("signal(SIGALRM) error");
  }
  if (setjmp(buf) != 0) {
    err_quit("read timeout error");
  }
  alarm(10);

  if ((n = read(STDIN_FILENO, line, MAXLINE)) < 0) {
    err_sys("read error");
  }
  alarm(0);

  write(STDOUT_FILENO, line, n);
  return 0;
}

static void sig_alrm(int signo) { /*nothing to do*/

  longjmp(buf, 1);
}
