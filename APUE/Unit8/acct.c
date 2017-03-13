#include "../include/apue.h"

int main(int argc, char const *argv[]) {
  pid_t pid;

  if ((pid = fork()) < 0) {
    err_sys("fork error");
  } else if (pid > 0) { /* parent */
    sleep(2);
    exit(2);
  }

  if ((pid = fork()) < 0) {
    err_sys("fork error");
  } else if (pid > 0) { /* child 1 */
    sleep(1);
    abort();
  }

  if ((pid = fork()) < 0) {
    err_sys("fork error");
  } else if (pid > 0) { /* child 2 */
    execl("/bin/dd", "dd", "if=/etc/passwd", "of=/dev/null", NULL);
    exit(7);
  }

  if ((pid = fork()) < 0) {
    err_sys("fork error");
  } else if (pid > 0) { /* child 3 */
    sleep(2);
    exit(0);
  }

  sleep(1); /* child 4 */
  kill(getpid(), SIGKILL);

  return 0;
}
