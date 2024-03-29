#include <stdio.h>
#include <unistd.h>

#include "../lib/_init.h"

#define BUF_LEN 1024

static const char *help = "Usage: hostname [ignored command line arguments]\n"
                          "or: true OPTION\n"
                          "Prints name of computer.\n"
                          "\n"
                          "--help     display this help and exit\n"
                          "--version  output version information and exit";

static const char *version = "hostname (libc) 0.0.1";

int main(int argc, char *argv[]) {
  if (util_setup((init_ops){
          .argc = argc, .argv = argv, .help = help, .version = version}) == 0)
    return 0;

  char name[BUF_LEN];
  int res = gethostname(name, BUF_LEN);
  if (res == 0)
    printf("%s\n", name);
  else
    return 0;
}
