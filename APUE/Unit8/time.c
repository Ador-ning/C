#include "../include/apue.h"
#include <sys/times.h>

/*#########################################*/
/*
*	Local Functions Delecration
*/
static void pr_times(clock_t, struct tms *, struct tms *);
static void do_cmd(const char *);

int main(int argc, char const *argv[]) {

  int i;

  setbuf(stdout, NULL); /* unbuffered */
  for (i = 1; i < argc; i++) {
    do_cmd(argv[i]);
  }

  return 0;
}

static void do_cmd(const char *str) {
  struct tms tmsst, tmsend;
  clock_t start, end;
  int status;

  printf("\ncommand = %s\n", str);

  if ((start = times(&tmsst)) == -1) {
    err_sys("time error");
  }

  if ((status = system(str)) < 0) {
    err_sys("system() error");
  }

  if ((end = times(&tmsend)) == -1) {
    err_sys("time error");
  }

  pr_times(end - start, &tmsst, &tmsend);
  pr_exit(status);
}

static void pr_times(clock_t real, struct tms *st, struct tms *end) {
  static long clk = 0;

  if (clk == 0) { /* fetch clock ticks per second first time */
    if ((clk = sysconf(_SC_CLK_TCK)) < 0) {
      err_sys("sysconf error");
    }
  }

  printf(" real: %7.2f\n", real / (double)clk);
  printf(" user: %7.2f\n", (end->tms_utime - st->tms_utime) / (double)clk);
  printf(" system: %7.2f\n", (end->tms_stime - st->tms_stime) / (double)clk);
  printf(" child user: %7.2f\n",
         (end->tms_cutime - st->tms_cutime) / (double)clk);
  printf(" child system: %7.2f\n",
         (end->tms_cstime - st->tms_cstime) / (double)clk);
}
