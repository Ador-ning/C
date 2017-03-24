#include "../include/apue.h"

int main(int argc, char const *argv[]) {

  int n;
  int fd[2];
  pid_t pid;
  char line[MAXLINE];

  if (pipe(fd) < 0) {
    err_sys("pipe error");
  }

  if ((pid = fork()) < 0) {
    err_sys("fork error");
  } else if (pid == 0) { /* child */
    /* code */
    close(fd[1]);
    n = read(fd[0], line, MAXLINE);
    write(STDOUT_FILENO, "child: ", 7); /* add to distinct it */
    write(STDOUT_FILENO, line, n);
  } else { /* parent */
    close(fd[0]);
    write(fd[1], "hello world\n", 12);
  }

  return 0;
}
