#include "apue.h"
#include <errno.h>
#include <stdarg.h>
#include <syslog.h>

static void log_doit(int, int, int, const char *fmt, va_list ap);

/*
*	Caller must define and set this: nonzero if
*	interactive, zero if daemonize
*/
extern int log_to_stderr; /*????  maybe in logsys can be show*/

/*
*	Initilize syslog(), if running as daemon
*/
void log_open(const char *ident, int option, int facility) {
  if (log_to_stderr == 0) {
    openlog(ident, option, facility);
  }
}

/*
*	Nonfatal error related to a system call.
*	Print a message with system's errno value and return.
*/
void log_ret(const char *fmt, ...) {
  va_list ap;

  va_start(ap, fmt);
  log_doit(1, errno, LOG_ERR, fmt, ap);
  va_end(ap);
}

/*
*	Fatal error related to a system call.
*	Print a message and terminate.
*/
void log_sys(const char *fmt, ...) {
  va_list ap;

  va_start(ap, fmt);
  log_doit(1, errno, LOG_ERR, fmt, ap);
  va_end(ap);
  exit(2);
}

/*
*	Nonfatal error unrelated to a system call.
*	Print a message and return.
*/
void log_msg(const char *fmt, ...) {
  va_list ap;

  va_start(ap, fmt);
  log_doit(0, errno, LOG_ERR, fmt, ap);
  va_end(ap);
}

/*
*	Fatal error unrelated to a system call.
* Print a message and terminate.
*/
void log_quit(const char *fmt, ...) {
  va_list ap;

  va_start(ap, fmt);
  log_doit(0, errno, LOG_ERR, fmt, ap);
  va_end(ap);
  exit(2);
}

/*
*	Fatal error related to a system call.
* Error number passed as an explict pararmeter.
*	Print a message and terminate.
*/
void log_exit(int error, const char *fmt, ...) {
  va_list ap;

  va_start(ap, fmt);
  log_doit(1, error, LOG_ERR, fmt, ap);
  va_end(ap);
  exit(2);
}

/*
*	Print a massage and return to caller.
* Caller specifies "errorflages" and "priority".
*/
static void log_doit(int errorflages, int error, int priority, const char *fmt,
                     va_list ap) {
  char buf[MAXLINE];

  vsnprintf(buf, MAXLINE - 1, fmt, ap);
  if (errorflages)
    snprintf(buf + strlen(buf), MAXLINE - strlen(buf) - 1, ":%s",
             strerror(error));

  strcat(buf, "\n");
  if (log_to_stderr) {
    fflush(stdout);
    fputs(buf, stderr);
    fflush(stderr);
  } else {
    syslog(priority, "%s", buf);
  }
}
