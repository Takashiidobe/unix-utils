#include "../lib/getopt.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/utsname.h>

#include "../lib/_init.h"

static const char *help = "Usage: uname\n"
                          "or: uname OPTION\n"
                          "Displays information about the computer.\n"
                          "\n"
                          "--help     display this help and exit\n"
                          "--version  output version information and exit";

static const char *version = "uname (libc) 0.0.1";

enum UNAME_OPTS {
  KERNEL_NAME = 1,
  NODE_NAME = 2,
  KERNEL_RELEASE = 4,
  KERNEL_VERSION = 8,
  MACHINE = 16,
  OPERATING_SYSTEM = 32,
  ALL_OPTS = 64,
};

int main(int argc, char *argv[]) {
  if (util_setup((init_ops){.argc = argc,
                       .argv = argv,
                       .help = help,
                       .version = version,
                       .do_not_use_short_version_flag = 1}) == 0)
    return 0;

  struct utsname uts;
  uname(&uts);

  static struct option long_options[] = {
      {"kernel-name", no_argument, 0, 's'},
      {"nodename", no_argument, 0, 'n'},
      {"kernel-release", no_argument, 0, 'r'},
      {"kernel-version", no_argument, 0, 'v'},
      {"machine", no_argument, 0, 'm'},
      {"operating-system", no_argument, 0, 'o'},
      {"all", no_argument, 0, 'a'},
  };

  size_t opts = 0;

  while (1) {
    int option_index = 0;

    int c = getopt_long(argc, argv, ":snrvmoa", long_options, &option_index);

    if (c == -1)
      break;

    switch (c) {
    case 's':
    case 'o':
      opts |= KERNEL_NAME;
      break;

    case 'n':
      opts |= NODE_NAME;
      break;

    case 'r':
      opts |= KERNEL_RELEASE;
      break;

    case 'v':
      opts |= KERNEL_VERSION;
      break;

    case 'm':
      opts |= MACHINE;
      break;

    case 'a':
      opts |= ALL_OPTS;
      break;

    case '?':
      printf("uname: invalid option -- '%s'\n"
             "Try 'uname --help for more information.\n",
             argv[optind - 1]);
      exit(1);

    default:
      exit(1);
    }
  }

  if (argc < 2)
    printf("%s ", uts.sysname);
  if (opts & KERNEL_NAME)
    printf("%s ", uts.sysname);
  if (opts & NODE_NAME)
    printf("%s ", uts.nodename);
  if (opts & KERNEL_RELEASE)
    printf("%s ", uts.release);
  if (opts & KERNEL_VERSION)
    printf("%s ", uts.version);
  if (opts & MACHINE)
    printf("%s ", uts.machine);
  if (opts & ALL_OPTS)
    printf("%s %s %s %s %s %s ", uts.sysname, uts.nodename, uts.release,
           uts.version, uts.machine, uts.sysname);

  exit(0);
}
