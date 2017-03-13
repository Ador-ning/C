#include "../include/apue.h"

int main(int argc, char const *argv[]) {
  /* code */
  int i;
  struct stat f;
  char *p;

  for (i = 0; i < argc; i++) {
    /* code */
    printf("%s:", argv[i]);
    if (lstat(argv[i], &f) < 0) {
      /* code */
      err_ret("\tlstat error.");
      continue;
    }

    if (S_ISREG(f.st_mode)) {
      /* code */
      p = "regular";
    } else if (S_ISDIR(f.st_mode)) {
      /* code */
      p = "directory";
    } else if (S_ISFIFO(f.st_mode)) {
      /* code */
      p = "fifo";
    } else if (S_ISCHR(f.st_mode)) {
      /* code */
      p = "character";
    } else if (S_ISBLK(f.st_mode)) {
      /* code */
      p = "block";
    } else if (S_ISLNK(f.st_mode)) {
      /* code */
      p = "linker";
    } else if (S_ISSOCK(f.st_mode)) {

      p = "socket";
    } else
      p = "#Unknown mode#";
    printf("%s\n", p);
  }
  return 0;
}
