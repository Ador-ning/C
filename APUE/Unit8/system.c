#include "../include/apue.h"
#include <sys/wait.h>

int main(int argc, char const *argv[]) {
  int status;

  if ((status = system("date")) < 0) {
    err_sys("system() error");
  }
  pr_exit(status);

  if ((status = system("nonsuchcommand")) < 0) {
    err_sys("system() error");
  }
  pr_exit(status);

  if ((status = system("who; exit 44")) < 0) {
    err_sys("system() error");
  }
  pr_exit(status);

  return 0;
}
