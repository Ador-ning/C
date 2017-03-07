#include "../lib/apue.h"

/*#######################################*/
/* Declaration */
static void myexit1(void);
static void myexit2(void);

int main(int argc, char const *argv[]) {
  /* code */
  if (atexit(myexit2) != 0)
    err_sys("can't register myexit2");

  if (atexit(myexit1) != 0)
    err_sys("can't register myexit1");
  if (atexit(myexit1) != 0)
    err_sys("can't register myexit1");

  printf("main is done.\n");
  return 0;
}

static void myexit1() { printf("first 1"); }

static void myexit2() { printf("first "); }
