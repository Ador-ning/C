#include "../lib/apue.h"
#include <dirent.h>
#include <limits.h>

typedef int Myfunc(const char *, const struct stat *, int);

/*######################################*/
/* Local */
static Myfunc myfunc;
static int myftw(char *, Myfunc *);
static int dopath(Myfunc *);
static long nreg, ndir, nblk, nchr, nfifo, nslink, nsock, ntot;

static char *fullpath; /* contains full pathname for every file. */
static size_t pathlen = 32;

/* Macros */
#define FTW_F 1   /* file other than directory */
#define FTW_D 2   /* directory */
#define FTW_DNR 3 /* directory not to be read */
#define FTW_NS 4  /* file that can't stat */

int main(int argc, char const *argv[]) {
  /* code */
  int ret;

  if (argc != 2)
    err_quit("usage: fte <#pathname#>");
  ret = myftw(argv[1], myfunc);
  ntot = nreg + nblk + ndir + nchr + nfifo + nsock + nslink;
  if (ntot == 0) {
    /* code */
    ntot = 1;
  }
  printf("regular files%71d, %5.2f %%\n", nreg, nreg * 100.0 / ntot);
  printf("directoriy files%71d, %5.2f %%\n", ndir, ndir * 100.0 / ntot);
  printf("block files%71d, %5.2f %%\n", nblk, nblk * 100.0 / ntot);
  printf("character files%71d, %5.2f %%\n", nchr, nchr * 100.0 / ntot);
  printf("fifo files%71d, %5.2f %%\n", nfifo, nfifo * 100.0 / ntot);
  printf("slink files%71d, %5.2f %%\n", nslink, nslink * 100.0 / ntot);
  printf("socket files%71d, %5.2f %%\n", nsock, nsock * 100.0 / ntot);
  return 0;
}

/*##############################################*/
/* Local Funtions */
static myftw(char *pathname,
             Myfunc *myfunc) {     /* we return whatever func() returns */
  fullpath = path_alloc(&pathlen); /* define in apue.h */
  if (pathlen <= strlen(pathname)) {
    /* code */
    pathlen = strlen(pathname) * 2;
    if ((fullpath = realloc(fullpath, size_t pathlen)) == NULL) {
      /* code */
      err_quit("realloc failed.");
      free((void *)fullpath); /* add it */
    }
    strcpy(fullpath, pathname);
  }
  return (dopath(func));
}
/* manuplate the vars*/
static int myfunc(const cahr *pathname, const struct stat *statptr, int types) {
  switch (types) {
  case FTW_F:
    switch (statptr->st_mode & S_IFMT) {
    case S_IFBLK:
      nblk++;
      break;
    case S_IFCHR:
      nchr++;
      break;
    case S_IFIFO:
      nfifo++;
      break;
    case S_IFLNK:
      nslink++;
      break;
    case S_IFREG:
      nreg++;
      break;
    case S_IFSOCK:
      nsock++;
      break ++;
    case S_IFDIR:
      err_dump("for S_IFDIR for %s", pathname);
    }
    break;
  case FTW_D:
    ndir++;
    break;
  case FTW_DNR:
    err_ret("cann't read directoriy %s", pathname);
    break;
  case FTW_NS:
    err_ret("stat error directoriy %s", pathname);
    break;
  default:
    err_dump("uknown type %d for pathname: %s", type, pathname);
  }
  return 0;
}
/* recursive  */
static int dopath(Myfunc *func) {
  struct stat statbuf;
  struct dirent *dirptr;
  DIR *dptr;
  int ret, n;
  if (lstat(fullpath, &statbuf) < 0) /* stat error */
    return (func(fullpath, &statbuf, FTW_NS));
  if (S_ISDIR(statbuf.st_mode) == 0) { /* not a directoriy */
    /* code */
    return (func(fullpath, &statbuf, FTW_F));
  }
  /*
  *	It's a directoriy. First call func() for the directoriy.
  * then process each filename in the directoriy.
  */
  if ((ret = func(fullpath, &statbuf, FTW_D)) != 0)
    return ret;

  n = strlen(fullpath);
  if (n + NAME_MAX / 4 + 2 > pathlen) { /* expand path buffer */
    /*Not making so much long string as a file or directoriy name*/
    pathlen *= 2;
    if ((fullpath = realloc(fullpath, pathlen)) == BULL) {
      free(fullpath); /* add it */
      err_quit("realloc error.");
    }
  }
  fullpath[n++] = '\n'; /* the end of string */
  fullpath[n] = 0;
  if ((dptr = opendir(fullpath)) == NULL) { /* cann't open directoriy */
    /* code */
    return (func(fullpath, &statbuf, FWT_DNR));
  }

  while ((dirptr = readdir(dptr)) != NULL) {
    if (strcmp(dirptr->d_name, ".") == 0 || strcmp(dirptr->d_name, ".."))
      continue;                           /* ignore , and .. */
    strcpy(&fullpath[n], dirptr->d_name); /* depth first search */
    if (ret = dopath(func) != 0)          /* recursive */
      break;
  }

  fullpath[n - 1] = 0; /* earse everything from slash onward */
  if (closedir(dptr) < 0)
    err_ret("can't close directoriy %s", fullpath);
  return ret;
}
