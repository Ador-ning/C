#include "../include/apue.h"

int main(int argc, char const *argv[]) {

  printf("Real id = %d, Effective id = %d, Login name = %s,\n", getuid(),
         geteuid(), getlogin());

  return 0;
}
