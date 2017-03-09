#include "../include/apue.h"

int main(int argc, char const *argv[]) {

  int i;
  char **ptr;
  extern char **environ;

  for (i = 0; i < argc; i++) { /* echo all command-line argvx */
    printf("argv[%d]: %s\n", i, argv[i]);
  }

  for (ptr = environ; *ptr != 0; ptr++) { /* and all env strings */
    printf("%s\n", *ptr);
  }

  return 0;
}
