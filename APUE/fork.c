#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char const *argv[]) {
  /* code */
  int fd;
  pid_t pid;
  pid = fork();
  // the using of fork()
  if (pid < 0) {
    perror("fork"); // error pid=-1
  } else if (pid > 0) {
    wait(NULL); // in parent
    exit(EXIT_FAILURE);
  } else { // in new procession
    if (fd = open("/dev/tty1", O_RDWR) == -1)
      perror("open");
    // open a new tty device to print the info of new procession
    printf("pid=%d, ppid=%d\n", getpid(), getppid()); // this ID and parent's ID
    printf("sid=%d, tcgetsid=%d\n", getsid(getpid()),
           tcgetsid(fd));                   // sesion's first procession ID and
    printf("pigd=%d\n", getpgid(getpid())); // procession group ID
  }
  return 0;
}
