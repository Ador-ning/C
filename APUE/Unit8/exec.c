#include "../lib/apue.h"
#include <sys/wait.h>

char *env_init[] = {"USER=unknown", "PATH=/tmp", NULL};

int main(int argc, char const *argv[]) {

  pid_t pid;

  if ((pid = fork()) < 0) {
    err_sys("error fork");
  } else if (pid == 0) {
    if (execle("../Unit8/echoall.c", "echoall", "myarg1", "My ARG2", (char *)0,
               env_init)) {
      err_sys("execle error");
    }
  }

  if (waitpid(pid, NULL, 0) != pid) {
    err_sys("wait error");
  }

  if ((pid = fork()) < 0) {
    err_sys("error fork");
  } else if (pid == 0) {
    if (execlp("echoall", "echoall", "only 1 arg", (char *)0) < 0) {
      err_sys("execlp error");
    }
  }

  return 0;
}
