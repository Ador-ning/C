#include "../lib/apue.h"
#include <sys/wait.h>

int main(int argc, char const *argv[]) {
  /* code */
  pid_t pid;
  int status;

  if ((pid = fork()) < 0)
    err_sys("error fork.");
  else if (pid == 0) { /* child */
    exit(7);
  }

  if (wait(&status) != pid) { /* wait for child */
    err_sys("wait error.");
  }

  pr_exit(status);

  if ((pid = fork()) < 0) {
    err_sys("error fork.");
  } else if (pid == 0) {
    status /= 0; /* divide by 0 generates SIGFPE */
  }

  if (wait(&status) != pid) {
    err_sys("wait error");
  }

  pr_exit(status);

  return 0;
}
