#include "apue.h"
#include <fcntl.h>
#include <stdarg.h>

/*
*	Declaration
*/
static void err_doit(int, int, const char *, va_list);

/*
* Realize our own error processing functions interface
*/
/**Fatal -- to descript the error can cause you die**/
// Nonfatal error related to a system call. print a message and return.
void err_ret(const char *fmt, ...) {
  va_list ap; // Define in file <stdarg.h>

  va_start(ap, fmt);
  err_doit(1, errno, fmt, ap);
  va_end(ap);
}

// Fatal error related to a system call. Print a message and terminate.
void err_sys(const char *fmt, ...) {
  va_list ap;

  va_start(ap, fmt);
  err_doit(1, errno, fmt, ap);
  va_end(ap);
  exit(1);
}

// Nonfatal error unrelated to a system call. error code passed as explict
// parameter. print a message and return.
void err_cont(int error, const char *fmt, ...) {
  va_list ap;

  va_start(ap, fmt);
  err_doit(1, error, fmt, ap);
  va_end(ap);
}

// Fatal error unrelated to a system call. error code
// passed as explict parameter
// Print a message and terminte it.
void err_exit(int error, const char *fmt, ...) {
  va_list ap;

  va_start(ap, fmt);
  err_doit(1, error, fmt, ap);
  va_end(ap);
  exit(1);
}

// Fatal error related to a system call.
// Print a message, dump core, and terminate it.
void err_dump(const char *fmt, ...) {
  va_list ap;

  va_start(ap, fmt);
  err_doit(1, errno, fmt, ap);
  va_end(ap);
  abort(); /*dump core */
  exit(1);
}

// Nonfatal error unrelated to system call.
// Print a message and return.
void err_msg(const char *fmt, ...) {
  va_list ap;

  va_start(ap, fmt);
  err_doit(0, 0, fmt, ap);
  va_end(ap);
}

// Fatal error unrelated to a system call .
// Print a message and terminate it.
void err_quit(const char *fmt, ...) {
  va_list ap;

  va_start(ap, fmt);
  err_doit(0, 0, fmt, ap);
  va_end(ap);
  exit(1);
}

static void err_doit(int errflag, int error, const char *fmt, va_list ap) {
  char buf[MAXLINE];

  vsnprintf(buf, MAXLINE, fmt, ap); // in file <stdio.h>

  if (errflag)
    snprintf(buf + strlen(buf), MAXLINE - strlen(buf) - 1, ":%s",
             strerror(error));
  strcat(buf, "\n");
  fflush(stdout);
  fputs(buf, stderr);
  fflush(NULL);
}

/*
*	Not here
*/
void pr_mask(const char *str) {
  sigset_t sigset;
  int errno_save;
  errno_save = errno;

  if (sigprocmask(0, NULL, &sigset)) {
    err_ret("sigprocmask error");
  } else {
    printf("%s\t", str);
    if (sigismember(&sigset, SIGINT))
      printf("SIGINT");
    if (sigismember(&sigset, SIGQUIT))
      printf("SIGQUIT");
    if (sigismember(&sigset, SIGUSR1))
      printf("SIGUSR1");
    if (sigismember(&sigset, SIGUSR2))
      printf("SIGUSR2");
    printf("\n");
  }

  errno = errno_save;
}
