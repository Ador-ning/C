#include "../include/apue.h"

int globval = 6;
const char buf[] = "a write to stdout\n";

int main(int argc, char const *argv[]) {
  /* code */
  int var;
  pid_t pid;

  var = 88;

  if (write(STDERR_FILENO, buf, sizeof(buf) - 1) !=
      sizeof(buf) - 1) { /* no IO buffer */
    err_sys("write error.");
  }

  printf("before fork\n");

  if ((pid = fork()) < 0) {
    /* code */
    err_sys("error fork.");
  } else if (pid == 0) { /* child */
    globval++;
    var -= 10;
  } else { /* parent */
    sleep(2);
    putchar((int)'\n');
  }

  printf("pid = %ld, glob = %d, var = %d\n", (long)getpid(), globval, var);
  return 0;
}
