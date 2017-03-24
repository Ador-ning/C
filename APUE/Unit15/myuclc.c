#include "../include/apue.h"
#include <ctype.h>

int main(int argc, char const *argv[]) {

  int c;

  while ((c = getchar()) != EOF) {
    if (isupper(c)) {
      c = tolower(c);
    }

    if (putchar(c) == EOF) {
      err_sys("output error");
    }

    if (c == '\n') {
      fflush(stdout);
    }
  }

  return 0;
}
