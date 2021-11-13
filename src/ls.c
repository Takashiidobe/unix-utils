#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include "../lib/_init.h"

static const char *help =
    "Usage: ls - list directory contents \n"
    "[OPTION]... [FILE]...\n"
    "List information about the FILEs (the current directory by default).\n"
    "\n"
    "--help     display this help and exit\n"
    "--version  output version information and exit";

static const char *version = "ls(libc) 0.0.1";

void reset_color() {
  printf("\033[0m");
}

void print_path(const char* s) {
  printf("%s ", s);
}

void blue(const char *s) {
  printf("\033[1;34m");
	print_path(s);
	reset_color();
}

void green(const char *s) {
  printf("\033[1;32m");
	print_path(s);
	reset_color();
}

int is_tty() {
	return isatty(fileno(stdout));
}

int main(int argc, char *argv[]) {
  if (util_setup((init_ops){
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
			const char* path = dir->d_name;
      if ((strcmp(path, ".") != 0) && (strcmp(path, "..") != 0)) {
				struct stat path_stat;
				stat(path, &path_stat);
				if (S_ISREG(path_stat.st_mode) && path_stat.st_mode & S_IXUSR) {
					if (is_tty()) green(path);
					else print_path(path);
				} else if (S_ISREG(path_stat.st_mode)) {
					print_path(path);
				} else {
					if (is_tty()) blue(path);
					else print_path(path);
				}
      }
    }
  }
  closedir(d);
}
