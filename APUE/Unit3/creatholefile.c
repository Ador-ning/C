#include "../lib/apue.h"
#include <fcntl.h>

const char buf1[] = "abcdefghij";
const char buf2[] = "ABCDEFGHIJ";

int main(int argc, char const *argv[]) {
  /* code */
  int fd;
  if ((fd = creat("file.hole", FILE_MODE)) < 0)
    err_sys("Creat Error");
  if (write(fd, buf1, 10) != 10)
    err_sys("buf1 write error");
  if (lseek(fd, 20, SEEK_SET) == -1)
    err_sys("lseek error");
  /*offset now = 20*/
  if (write(fd, buf2, 10) != 10)
    err_sys("buf2 write error.");
  /*offset now = 30*/

  return 0;
}
