#include <stdio.h>
#include <string.h>

#include "../lib/_init.h"

static const char *help = "Usage: base32 [ignored command line arguments]\n"
                          "or: base32 OPTION\n"
                          "Exit with a status code indicating success.\n"
                          "\n"
                          "--help     display this help and exit\n"
                          "--version  output version information and exit";

static const char *version = "base32 (libc) 0.0.1";

int main(int argc, char *argv[]) {
  if (_init((init_ops){
          .argc = argc, .argv = argv, .help = help, .version = version}) == 0)
    return 0;

  return 0;
}
