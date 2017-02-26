#include "apue"
#include <dirent.h>
#include <unistd.h> /* Provide the unix standard functions prototypes*/

/*
*	Local Functions
*/
static void sig_int(int signo) { printf("interrupte.\n%%"); }

/*
*	The Prototypes in unit1 changed , declare here.
* There can be made perfectly later.
*/

/*
* pararmeter1 - the count of input command in terminal.
*	pararmeter2 - the route of directory
* Thinking directly input the command
* improve - options , diffirent route types, permissions
*/
void myls(int count, const char *directory) {
  DIR *d;              /*The structure to open a directory*/
  struct dirent *dirp; /*The structure to read DIR */
  if (count != 2)
    err_quit("usage: ls directory_name.");

  if ((d = opendir(directory)) == NULL)
    err_sys("can't open %s", directory); /*Descript the reason*/
  while ((dirp = readdir(d)) !=
         NULL) /*In here can manuplate the style to show in terminal*/
    printf("%s\n", dirp->d_name);
  closedir(d);
  return 0;
}

/*
*
*/
void mystdio() {
  int n;
  char buf[MAXLINE / 4]; /*1K*/

  while ((n = read(STDIN_FILENO, buf, MAXLINE / 4)) > 0)
    if (write(STDOUT_FILENO, buf, MAXNAMLEN / 4) != n)
      err_sys("writte error.");
  if (n < 0)
    err_sys("read error.");
  exit(0);
}

/*
*
*/
void mychario() {
  int c;

  while ((c = getc(stdin)) != EOF)
    if (putc(c, stdout) == EOF)
      err_sys("Output Error.");
  if (ferror(stdin))
    err_sys("input error.");
}

/*
*
*/
void myshell() {
  char buf[MAXLINE];
  pid_t pid;
  int status;
  /*The signal processing part, sig_int -- the function defination by user.*/
  if (signal(SIGINT, sig_int) == SIG_ERR)
    err_sys("signal error.");

  printf("%%");
  while (fgets(buf, MAXLINE, stdin) != NULL) {
    if (buf[strlen(buf) - 1] == '\n')
      buf[strlen(buf) - 1] = 0; /*Replace newline with null*/

    if ((pid = fork()) < 0)
      err_sys("fork error.");
    else if (pid == 0) { /*in child*/
      execlp(buf, buf, (char *)0);
      err_ret("couldn't execute: %s", buf);
      exit(127);
    }

    /*parent*/
    if ((pid = waitpid(pid, &status)) < 0)
      err_sys("waitpid error.");
    printf("%%\n");
  }
  exit(0);
}

int main(int argc, char const *argv[]) {
  /* code */
  return 0;
}
