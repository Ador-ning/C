#include "../include/apue.h"
#include <dirent.h>

int main(int argc, char *argv[]) {
  DIR *dp;
  struct dirent *dirp;

  if (argc != 2)
    err_quit("usage: ls directory_name");

  if ((dp = opendir(argv[1])) == NULL)
    err_sys("can't open %s", argv[1]);
  int i = 0;
  /* Tab */
  while ((dirp = readdir(dp)) != NULL) {
    printf("%s %llu %d ", dirp->d_name, dirp->d_ino, dirp->d_namlen);
    if (i % 2 != 0) {
      putchar((int)'\n');
    }
    i++;
  }

  closedir(dp);
  exit(0);
}
