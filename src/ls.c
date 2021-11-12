#include <dirent.h>
#include <stdio.h>
#include <string.h>

#include "../lib/_init.h"

static const char *help =
    "Usage: ls - list directory contents \n"
    "[OPTION]... [FILE]...\n"
    "List information about the FILEs (the current directory by default).\n"
    "\n"
    "--help     display this help and exit\n"
    "--version  output version information and exit";

static const char *version = "ls(libc) 0.0.1";

int main(int argc, char *argv[]) {
  if (_init((init_ops){
          .argc = argc, .argv = argv, .help = help, .version = version}) == 0)
    return 0;

  DIR *d;
  struct dirent *dir;
  if (argc == 1) {
    argv[1] = ".";
  }
  d = opendir(argv[1]);
  if (d != NULL) {
    while ((dir = readdir(d)) != NULL) {
      if ((strcmp(dir->d_name, ".") != 0) && (strcmp(dir->d_name, "..") != 0))
        printf("%s\n", dir->d_name);
    }
    closedir(d);
  }
}
