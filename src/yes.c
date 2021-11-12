#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "../lib/_init.h"

static const char *help = "Usage: yes [ARGUMENTS]...\n"
                          "or: yes OPTION\n"
                          "Print 'y' or Arguments repeatedly.\n"
                          "\n"
                          "--help     display this help and exit\n"
                          "--version  output version information and exit";

static const char *version = "yes (libc) 0.0.1";

int main(int argc, char *argv[]) {
  if (_init((init_ops){
          .argc = argc, .argv = argv, .help = help, .version = version}) == 0)
    return 0;

  if (argc < 2) {
    while (1) {
      puts("y");
    }
  }

  while (1) {
    puts(argv[1]);
  }
}
