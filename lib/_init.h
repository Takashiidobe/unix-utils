#ifndef _UNIX_UTIL_H
#define _UNIX_UTIL_H

#include <string.h>
#include <stdio.h>

typedef struct init_ops {
  int argc;
  char** argv;
  const char *help;
  const char* version;
  int print_help_by_default;
  int do_not_use_short_help_flag;
  int do_not_use_long_help_flag;
  int do_not_use_short_version_flag;
  int do_not_use_long_version_flag;
} init_ops;

int _init(init_ops ops);

#endif
