#include <errno.h>
#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <string.h>

#include "../lib/_init.h"

static const char *help =
    "Usage: whoami [ignored command line arguments]\n"
    "or: whoami OPTION\n"
    "Print the username associated with the current effective user ID.\n"
    "Same as id -un.\n"
    "\n"
    "--help     display this help and exit\n"
    "--version  output version information and exit";

static const char *version = "whoami (libc) 0.0.1";

int main(int argc, char *argv[]) {
  if (_init((init_ops){
          .argc = argc, .argv = argv, .help = help, .version = version}) == 0)
    return 0;

  uid_t uid = geteuid();

  struct passwd *pw = (uid == errno ? NULL : getpwuid(uid));
  if (!pw) {
    printf("Cannot find name for user ID %u\n", uid);
    return EXIT_FAILURE;
  }
  puts(pw->pw_name);

  return EXIT_SUCCESS;
}
