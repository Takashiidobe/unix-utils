#include <stdio.h>
#include <string.h>

#include "../lib/_init.h"

static const char *help = "Usage: tac [FILE]...\n"
                          "or: tac OPTION\n"
                          "Exit with a status code indicating success.\n"
                          "\n"
                          "--help     display this help and exit\n"
                          "--version  output version information and exit";

static const char *version = "tac (libc) 0.0.1";

int main(int argc, char *argv[]) {
  if (util_setup((init_ops){
          .argc = argc, .argv = argv, .help = help, .version = version}) == 0)
    return 0;

  return 0;
}
