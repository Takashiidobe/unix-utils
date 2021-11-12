#include "../lib/_init.h"
#include <stdlib.h>
#include <unistd.h>

static const char *help = "Usage: sleep OPTION\n"
                          "Exit with a status code indicating success.\n"
                          "\n"
                          "--help     display this help and exit\n"
                          "--version  output version information and exit";

static const char *version = "sleep (libc) 0.0.1";

int main(int argc, char *argv[]) {
  if (_init((init_ops){.argc = argc,
                       .argv = argv,
                       .help = help,
                       .version = version,
                       .print_help_by_default = 1}) == 0)
    return 0;

  if (argc > 1) {
    sleep(atoi(argv[1]));
  }

  return 0;
}
