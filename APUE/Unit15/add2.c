#include "../include/apue.h"

int main(int argc, char const *argv[]) {

  int n, n1, n2;

  char line[MAXLINE];

  while ((n = read(STDIN_FILENO, line, MAXLINE)) > 0) {
    line[n] = 0; /* 0 -> n-1*/
    if (sscanf(line, "%d%d", &n1, &n2) == 2) {
      sprintf(line, "%d\n", n1 + n2);

      n = strlen(line);
      if (write(STDOUT_FILENO, line, n) != n) {
        err_sys("write error");
      }
    } else {
      if (write(STDOUT_FILENO, "invaild args\n", 13) != 13) {
        err_sys("write error");
      }
    }
  }

  return 0;
}
