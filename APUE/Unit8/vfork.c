#include "../include/apue.h"

int globval = 6;
const char buf[] = "a write to stdout\n";

int main(int argc, char const *argv[]) {
  /* code */
  volatile int var = 88;
  pid_t pid;

  if (write(STDERR_FILENO, buf, sizeof(buf) - 1) !=
      sizeof(buf) - 1) { /* no IO buffer */
    err_sys("write error.");
  }

  printf("before fork\n");

  if ((pid = vfork()) < 0) {
    /* code */
    err_sys("error vfork.");
  } else if (pid == 0) { /* child */
    globval++;
    var -= 10;
    _exit(0); /* terminates */
  }
  /* parent continue */

  printf("pid = %ld, glob = %d, var = %d\n", (long)getpid(), globval, var);
  return 0;
}
