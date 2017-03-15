
#include "../include/apue.h"
#include <pwd.h>

/*######################################*/
static void my_alarm(int signo) {
  struct passwd *rootptr;
  printf("in signal hanler\n");
  if ((rootptr = getpwnam("ning")) == NULL) {
    err_sys("get root password error");
  }
  printf("%s %s %s", rootptr->pw_name, rootptr->pw_passwd, rootptr->pw_shell);
  alarm(1); /* conduct the SIGALRM */
}

int main(int argc, char const *argv[]) {

  struct passwd *ptr;

  signal(SIGALRM, my_alarm);

  for (;;) {
    if ((ptr = getpwnam("ning")) == NULL) {
      err_sys("get ning password error");
    }

    if (strcmp(ptr->pw_name, "ning") != 0) {
      printf("return value corrupted! , pw_name: %s\n", ptr->pw_name);
    }
  }
  return 0;
}
