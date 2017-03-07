#include "../lib/apue.h"

/*######################################*/
/*
*	Functions Prototypes
*/
int is_unbuffered(FILE *);
int is_linebuffered(FILE *);
int buffersize(FILE *);
void pr_stdio(const char *, FILE *);
/*######################################*/

int main(int argc, char const *argv[]) {
  /* code */
  FILE *fp;
  fputs("enter any character \n", stdout);
  if (getchar() == EOF)
    err_sys("getchar error.");

  pr_stdio("stdin", stdin);
  pr_stdio("stdout", stdout);
  pr_stdio("stderr", stderr);

  if ((fp = fopen("/etc/passwd", "r")) == NULL)
    err_sys("fopen error");
  if (getc(fp) == EOF)
    err_sys("getc error");
  pr_stdio("/etc/passwd", fp);
  exit(0);
}

/*#######################################*/
void pr_stdio(const char *name, FILE *fp) {
  printf("stream=%s", name);
  if (is_linebuffered(fp))
    printf("\tline buffer");
  else if (is_unbuffered(fp))
    printf("\tunbuffer");
  else
    printf("fully buffer");
  printf(", buffer size = %d", buffersize(fp));
}

#if define(_IO_UNBUFFERED)
int is_unbuffered(fp) { return (fp->_flags & _IO_UNBUFFERED); }

int is_linebuffered(fp) { return (fp->_flags & _IO_LINE_BUF); }

int buffersize(fp) { return (fp->_IO_buf_end - fp->_IO_buf_base); }
#elif define(__SNBF)
int is_unbuffered(fp) { return (fp->_flags & __SNBF); }

int is_linebuffered(fp) { return (fp->_flags & _SLBF); }

int buffersize(fp) { return (fp->_bf._size); }
#elif define(_IONBF)

#ifdef _LP64
#define _flag_pad [4]
#define _ptr_pad [1]
#define _base_pad [2]
#endif

int is_unbuffered(fp) { return (fp->_flags & _IONBF); }

int is_linebuffered(fp) { return (fp->_flags & _IOLBF); }

int buffersize(fp) {
#idef _LP64
  return (fp->_base - fp->_ptr);
#else
return (BUFSIZ);
#endif
}
#else
/*#unknown#*/
#endif
