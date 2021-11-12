#include <errno.h>
#include <stdio.h>
#include <unistd.h>

#include "../lib/_init.h"

static const char *help = "Usage: rmdir dir1...dirn\n"
                          "or: rmdir OPTION\n"
                          "Deletes all dirs provided. Sets errno on error.\n"
                          "\n"
                          "--help     display this help and exit\n"
                          "--version  output version information and exit";

static const char *version = "rmdir (libc) 0.0.1";

int main(int argc, char *argv[]) {
  if (_init((init_ops){
          .argc = argc, .argv = argv, .help = help, .version = version}) == 0)
    return 0;

  for (size_t i = 1; i < argc; i++) {
    int res = rmdir(argv[i]);

    if (res == 0)
      continue;

    if (errno == 2) {
      printf("%s\n", "The directory does not exist.");
      goto error;
    } else if (errno == 13) {
      printf("%s\n", "Permission denied.");
      goto error;
    } else if (errno == 66) {
      printf("%s\n", "Directory is not empty.");
      goto error;
    }
  }

  return 0;
error:
  return 1;
}
