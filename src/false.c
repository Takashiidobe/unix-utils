#include <stdio.h>

#include "../lib/_init.h"

static const char *help = "Usage: false [ignored command line arguments]\n"
                          "or: false OPTION\n"
                          "Exit with a status code indicating failure.\n"
                          "\n"
                          "--help     display this help and exit\n"
                          "--version  output version information and exit";

static const char *version = "false (libc) 0.0.1";

int main(int argc, char *argv[]) {
  if (_init((init_ops){
          .argc = argc, .argv = argv, .help = help, .version = version}) == 0)
    return 0;
  return 1;
}
