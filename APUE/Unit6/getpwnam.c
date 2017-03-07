#include "../lib/apue.h"
#include <pwd.h> /* contains the structure of passwd */
#include <stddef.h>
#include <string.h>

struct passwd *getpwnam(const char *name) {
  struct passwd *ptr;

  setpwent();
  while ((ptr = getpwent()) != NULL) {
    if (strcmp(name, ptr->pw_name) == 0)
      break; /* find a match */
  }
  endpwent();
  return (ptr);
}
