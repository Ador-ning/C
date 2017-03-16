#include "../include/apue.h"

/*######################################*/
static void err_doit(int errflag, int error, const char *fmt, va_list ap) {
  char buf[MAXLINE];

  vsnprintf(buf, MAXLINE, fmt, ap); /* in file <stdio.h> */

  if (errflag)
    snprintf(buf + strlen(buf), MAXLINE - strlen(buf) - 1, ":%s",
             strerror(error));
  strcat(buf, "\n");
  fflush(stdout);
  fputs(buf, stderr);
  fflush(NULL);
}
/*###################################*/

/*###################################*/
/* Processing Errors functions */
/* Nonfatal error related to a system call. print a message and return. */
void err_ret(const char *fmt, ...) {
  va_list ap; /* Define in file <stdarg.h>*/

  va_start(ap, fmt);
  err_doit(1, errno, fmt, ap);
  va_end(ap);
}

/* Fatal error related to a system call. Print a message and terminate. */
void err_sys(const char *fmt, ...) {
  va_list ap;

  va_start(ap, fmt);
  err_doit(1, errno, fmt, ap);
  va_end(ap);
  exit(1);
}

/* Nonfatal error unrelated to a system call. error code passed as explict
* parameter. print a message and return.
*/
void err_cont(int error, const char *fmt, ...) {
  va_list ap;

  va_start(ap, fmt);
  err_doit(1, error, fmt, ap);
  va_end(ap);
}

/* Fatal error unrelated to a system call. error code
* passed as explict parameter
* Print a message and terminte it.
*/
void err_exit(int error, const char *fmt, ...) {
  va_list ap;

  va_start(ap, fmt);
  err_doit(1, error, fmt, ap);
  va_end(ap);
  exit(1);
}

/* Fatal error related to a system call.
* Print a message, dump core, and terminate it.
*/
void err_dump(const char *fmt, ...) {
  va_list ap;

  va_start(ap, fmt);
  err_doit(1, errno, fmt, ap);
  va_end(ap);
  abort(); /*dump core */
  exit(1);
}

/* Nonfatal error unrelated to system call.
* Print a message and return.
*/
void err_msg(const char *fmt, ...) {
  va_list ap;

  va_start(ap, fmt);
  err_doit(0, 0, fmt, ap);
  va_end(ap);
}

/* Fatal error unrelated to a system call .
* Print a message and terminate it.
*/
void err_quit(const char *fmt, ...) {
  va_list ap;

  va_start(ap, fmt);
  err_doit(0, 0, fmt, ap);
  va_end(ap);
  exit(1);
}
