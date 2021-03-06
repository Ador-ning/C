#include "../include/apue.h"

/* signal handler */
static void sig_pipe(int);

int main(int argc, char const *argv[]) {
  int n, fd1[2], fd2[2];
  pid_t pid;
  char line[MAXLINE];

  if (signal(SIGPIPE, sig_pipe) == SIG_ERR) {
    err_sys("signal error");
  }

  if (pipe(fd1) < 0 || pipe(fd2) < 0) {
    err_quit("pipe creat error");
  }

  if ((pid = fork()) < 0) {
    err_sys("fork error");
  } else if (pid == 0) { /*child*/
    close(fd1[1]);
    close(fd2[0]);

    if (fd1[0] != STDIN_FILENO) {
      if (dup2(fd1[0], STDIN_FILENO) != STDIN_FILENO) {
        err_sys("dup2 error to stdin");
      }
      close(fd1[0]);
    }
    if (fd2[1] != STDOUT_FILENO) {
      if (dup2(fd2[1], STDOUT_FILENO) != STDOUT_FILENO) {
        err_sys("dup2 error to stdout");
      }
      close(fd2[1]);
    }

    if (execl("./add2", "add2", (char *)0) < 0) {
      err_sys("execl error");
    }

    exit(0);
  } else {
    /* parent */
    close(fd1[0]);
    close(fd2[1]);

    while (fgets(line, MAXLINE, stdin) != NULL) { /* Have Inputting */
      n = strlen(line);
      if (write(fd1[1], line, n) != n) { /* Providing argvs to add2 */
        err_sys("write error pipe");
      }

      if (read(fd2[0], line, MAXLINE) < 0) { /* Read the result from add2 */
        err_sys("read error from pipe");
      }

      if (n == 0) {
        err_msg("child closed pipe");
        break;
      }
      if (fputs(line, stdout) == EOF) {
        err_sys("fputs error");
      }
    }

    if (ferror(stdin)) {
      err_sys("fgets error on stdin");
    }

    exit(0);
  }
}

static void sig_pipe(int signo) {
  printf("SIGPIPE caught\n");
  exit(1);
}
