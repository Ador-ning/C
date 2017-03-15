#include "../include/apue.h"

static void sig_int(int signo) { printf("caught SIGINT\n"); }
static void sig_chld(int signo) { printf("caught SIGCHLD\n"); }

int main(int argc, char const *argv[]) {

  if (signal(SIGINT, sig_int) == SIG_ERR) {
    err_sys("signal -- SIGINT error");
  }

  if (signal(SIGCHLD, sig_chld) == SIG_ERR) {
    err_sys("signal -- SIGCHLD error");
  }

  if (system("/bin/bd") < 0) {
    err_sys("system ed error");
  }
  return 0;
}
