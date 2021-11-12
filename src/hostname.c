#include <stdio.h>
#include <unistd.h>

#include "../lib/_init.h"

static const char *help = "Usage: hostname [ignored command line arguments]\n"
                          "or: true OPTION\n"
                          "Prints name of computer.\n"
                          "\n"
                          "--help     display this help and exit\n"
                          "--version  output version information and exit";

static const char *version = "hostname (libc) 0.0.1";

int main(int argc, char *argv[]) {
  if (_init((init_ops){
          .argc = argc, .argv = argv, .help = help, .version = version}) == 0)
    return 0;

  char name[1024];
  size_t len = 1024;
  int res = gethostname(name, len);
  if (res == 0)
    printf("%s\n", name);
  else
    return 0;
}
