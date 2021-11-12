#include "_init.h"

int _init(init_ops ops) {
  if (ops.argc < 2 && ops.print_help_by_default) {
    printf("%s\n", ops.help);
    goto success;
  } else if (ops.argc < 2 && !ops.print_help_by_default) {
    goto skip;
  } else if (strcmp(ops.argv[1], "--help") == 0 &&
             !ops.do_not_use_long_help_flag) {
    printf("%s\n", ops.help);
    goto success;
  } else if (strcmp(ops.argv[1], "-h") == 0 &&
             !ops.do_not_use_short_help_flag) {
    printf("%s\n", ops.help);
    goto success;
  } else if (strcmp(ops.argv[1], "--version") == 0 &&
             !ops.do_not_use_long_version_flag) {
    printf("%s\n", ops.version);
    goto success;
  } else if (strcmp(ops.argv[1], "-v") == 0 &&
             !ops.do_not_use_short_version_flag) {
    printf("%s\n", ops.version);
    goto success;
  } else {
    goto skip;
  }
success:
  return 0;
skip:
  return 1;
}
