#include "../lib/_init.h"
#include <stdio.h>
#include <stdlib.h>

static const char *help = "Usage: logname\n"
                          "or: logname OPTION\n"
                          "Exit with a status code indicating success.\n"
                          "\n"
                          "--help     display this help and exit\n"
                          "--version  output version information and exit";

static const char *version = "logname (libc) 0.0.1";

int main(int argc, char *argv[]) {
  if (_init((init_ops){
          .argc = argc, .argv = argv, .help = help, .version = version}) == 0)
    return 0;

  // char *cp = getlogin();
  // if (cp) {
  //   puts(cp);
  //   exit(0);
  // }
  // fprintf(stderr, "%s: no login name\n", argv[0]);
  // exit(1);
}
