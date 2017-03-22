#include "../include/apue.h"
#include "./daemonize.h"

int main(int argc, char const *argv[]) {
  daemonize("command");
  return 0;
}
