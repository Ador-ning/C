#include "../include/apue.h"
#include <errno.h>

/*###############################################*/
/*
* Local Fuctions
*/
static void sig_hup(int signo) {
  printf("SIGHUP received, pid = %ld\n", (long)getpid());
}

static void pr_ids(char *name) {
  printf("%s: pid = %ld, ppid = %ld, gpid = %ld, tpgid = %ld\n", name,
         (long)getpid(), (long)getppid(), (long)getpgrp(),
         (long)tcgetpgrp(STDIN_FILENO));
  fflush(stdout);
}

int main(int argc, char const *argv[]) {
  char c;
  pid_t pid;
  pr_ids("parent");

  if ((pid = fork()) < 0) {
    err_sys("fork error");
  } else if (pid > 0) { /* parent */
    sleep(6);
  } else { /* child */
    pr_ids("child");
    signal(SIGHUP, sig_hup);
    kill(getpid(), SIGTSTP); /* stop */
    pr_ids("child");
    if (rea·d(STDIN_FILENO, &c, 1) != 1) {
      printf("read error %d on controlling TTY\n", errno);
    }
  }

  return 0;
}