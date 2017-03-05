#include "../include/apue.h"
#include <setjmp.h>

/*#######################################*/
/* Local Functions Declaration */
static void f1(int, int, int, int);
static void f2(void);

/*######################################*/
/* Global Vars */
/*
*	key -- static has diff function in var and a function
*/
static int globval;
static jmp_buf jumpbuffer;

int main(int argc, char const *argv[]) {
  /* code */
  int autoval;
  register int regval;
  volatile int volval;
  static int statval;
  globval = 1;
  autoval = 2;
  regval = 3;
  volval = 4;
  statval = 5;

  if (setjmp(jumpbuffer) != 0) {
    /* code */
    printf("after longjmp:\n");
    printf(
        "globval = %d, autoval = %d, regval = %d, volval = %d, statval = %d\n",
        globval, autoval, regval, volval, statval);
    exit(0);
  }

  /* change variables after setjmp, but before longjmp. */
  globval = 11;
  autoval = 12;
  regval = 13;
  volval = 14;
  statval = 15;
  f1(autoval, regval, volval, statval); /* no return */

  return 0;
}

/*#######################################*/
static void f1(int a, int b, int c, int d) {
  printf("In f1():\n");
  printf("globval = %d, autoval = %d, regval = %d, volval = %d, statval = %d\n",
         globval, a, b, c, d);
  f2();
}

static void f2(void) { longjmp(jumpbuffer, 1); }
