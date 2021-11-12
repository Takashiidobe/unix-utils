#include <limits.h>
#include <stdio.h>
#include <unistd.h>

#include "../lib/_init.h"

static const char *help = "Usage: pwd [ignored command line arguments]\n"
                          "or: pwd OPTION\n"
                          "Prints the current working directory.\n"
                          "\n"
                          "--help     display this help and exit\n"
                          "--version  output version information and exit";

static const char *version = "pwd (libc) 0.0.1";

int main(int argc, char *argv[]) {
  if (_init((init_ops){
          .argc = argc, .argv = argv, .help = help, .version = version}) == 0)
    return 0;

  if (argc > 1) {
    printf("pwd: Expected 0 args, got %d\n", argc - 1);
    return 1;
  }

  char cwd[PATH_MAX];

  if (getcwd(cwd, sizeof(cwd)) != NULL) {
    printf("%s\n", cwd);
    return 0;
  } else {
    perror("Error getting pwd");
    return 1;
  }
}
