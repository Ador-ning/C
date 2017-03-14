#include "../include/apue.h"

/*#######################################*/
static void sig_int(int);

int main(int argc, char const *argv[]) {
  unsigned int unslept;

  if (signal(SIGINT, sig_int) == SIG_ERR) {
    err_sys("signal - SIGINT error");
  }

  unslept = sleep2(5);
  printf("sleep2 returned: %u\n", unslept);

  return 0;
}

static void sig_int(int signo) {
  int i, j;
  volatile long long k = 0;

  printf("\nsig_int starting\n");
  for (i = 0; i < 30000; i++) {
    for (j = 0; j < 5000; j++) {
      k++;
    }
  }
  printf("Loop times %lld\n", k);
}
