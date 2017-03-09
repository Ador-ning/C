/*
 * Our own header, to be included before all standard system headers.
 */
#ifndef _APUE_H
#define _APUE_H

#define _POSIX_C_SOURCE 200809L

#if defined(SOLARIS) /* Solaris 10 */
#define _XOPEN_SOURCE 600
#else
#define _XOPEN_SOURCE 700
#endif

#include <sys/signal.h>
#include <sys/stat.h>
#include <sys/termios.h> /* for winsize */
#include <sys/types.h>   /* some systems still require this */

#if defined(MACOS) || !defined(TIOCGWINSZ)
#include <sys/ioctl.h>
#endif

#include <errno.h>
#include <signal.h> /* for SIG_ERR */
#include <stdarg.h>
#include <stddef.h> /* for offsetof */
#include <stdio.h>  /* for convenience */
#include <stdlib.h> /* for convenience */
#include <string.h> /* for convenience */
#include <unistd.h> /* for convenience */

/*######################################*/
#define MEM_MAX 8192
#define MAXLINE 4096 /* max line length */
#define PATH_MAX 128
/*
 * Default file access permissions for new files.
 */
#define FILE_MODE (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)

/*
 * Default permissions for new directories.
 */
#define DIR_MODE (FILE_MODE | S_IXUSR | S_IXGRP | S_IXOTH)

typedef void Sigfunc(int); /* for signal handlers */

#define min(a, b) ((a) < (b) ? (a) : (b))
#define max(a, b) ((a) > (b) ? (a) : (b))
/*######################################*/

/*
 * Prototypes for our own functions.
 */
/* done */
char *path_alloc(size_t *); /* {Prog pathalloc} 2.16*/
long open_max(void);        /* {Prog openmax} 2.17*/

int set_cloexec(int); /* {Prog setfd} 13.9*/

/* done */
void clr_fl(int, int);
void set_fl(int, int); /* {Prog setfl} 3.12*/

void pr_mask(const char *);           /* {Prog prmask} 10.14*/
Sigfunc *signal_intr(int, Sigfunc *); /* {Prog signal_intr_function}  10.19*/

void daemonize(const char *); /* {Prog daemoninit} 13.1*/

void sleep_us(unsigned int);               /* {Ex sleepus} Exercise 14.5*/
ssize_t readn(int, void *, size_t);        /* {Prog readn_writen} 14.24*/
ssize_t writen(int, const void *, size_t); /* {Prog readn_writen} 14.24*/

int fd_pipe(int *); /* {Prog sock_fdpipe} 17.2*/
int recv_fd(int, ssize_t (*func)(int, const void *,
                                 size_t)); /* {Prog recvfd_sockets} 17.14*/
int send_fd(int, int);                     /* {Prog sendfd_sockets} 17.13*/
int send_err(int, int, const char *);      /* {Prog senderr} 17.12*/
int serv_listen(const char *);             /* {Prog servlisten_sockets} 17.8*/
int serv_accept(int, uid_t *);             /* {Prog servaccept_sockets} 17.9*/
int cli_conn(const char *);                /* {Prog cliconn_sockets} 17.10*/
int buf_args(char *, int (*func)(int, char **)); /* {Prog bufargs} 17.20*/

int tty_cbreak(int);               /* {Prog raw} 18.20*/
int tty_raw(int);                  /* {Prog raw} 18.20*/
int tty_reset(int);                /* {Prog raw} 18.20*/
void tty_atexit(void);             /* {Prog raw} 18.20*/
struct termios *tty_termios(void); /* {Prog raw} 18.20*/

int ptym_open(char *, int); /* {Prog ptyopen} 19.9*/
int ptys_open(char *);      /* {Prog ptyopen} 19.9*/

#ifdef TIOCGWINSZ
pid_t pty_fork(int *, char *, int, const struct termios *,
               const struct winsize *); /* {Prog ptyfork} 19.10*/
#endif

int lock_reg(int, int, int, off_t, int, off_t); /* {Prog lockreg} 14.5*/
/*
*	Lock
*/
#define read_lock(fd, offset, whence, len)                                     \
  lock_reg((fd), F_SETLK, F_RDLCK, (offset), (whence), (len))
#define readw_lock(fd, offset, whence, len)                                    \
  lock_reg((fd), F_SETLKW, F_RDLCK, (offset), (whence), (len))
#define write_lock(fd, offset, whence, len)                                    \
  lock_reg((fd), F_SETLK, F_WRLCK, (offset), (whence), (len))
#define writew_lock(fd, offset, whence, len)                                   \
  lock_reg((fd), F_SETLKW, F_WRLCK, (offset), (whence), (len))
#define un_lock(fd, offset, whence, len)                                       \
  lock_reg((fd), F_SETLK, F_UNLCK, (offset), (whence), (len))

pid_t lock_test(int, int, off_t, int, off_t); /* {Prog locktest} */

#define is_read_lockable(fd, offset, whence, len)                              \
  (lock_test((fd), F_RDLCK, (offset), (whence), (len)) == 0)
#define is_write_lockable(fd, offset, whence, len)                             \
  (lock_test((fd), F_WRLCK, (offset), (whence), (len)) == 0)

/*
*	Error Processing to Realize for procession
*/
/* done */
void err_msg(const char *, ...); /* {App misc_source} */
void err_dump(const char *, ...) __attribute__((noreturn));
void err_quit(const char *, ...) __attribute__((noreturn));
void err_cont(int, const char *, ...);
void err_exit(int, const char *, ...) __attribute__((noreturn));
void err_ret(const char *, ...);
void err_sys(const char *, ...) __attribute__((noreturn));
/*
*	Error Processing to Realize for daemon procession
*/
/* done */
void log_msg(const char *, ...); /* {App misc_source} Part 13*/
void log_open(const char *, int, int);
void log_quit(const char *, ...) __attribute__((noreturn));
void log_ret(const char *, ...);
void log_sys(const char *, ...) __attribute__((noreturn));
void log_exit(int, const char *, ...) __attribute__((noreturn));

/* done */
void TELL_WAIT(
    void); /* parent/child from {Sec race_conditions} In Section 8.9*/
void TELL_PARENT(pid_t);
void TELL_CHILD(pid_t);
void WAIT_PARENT(void);
void WAIT_CHILD(void);
void pr_exit(int); /* {Prog prexit} 8.5*/

#endif /* APUR_H */
