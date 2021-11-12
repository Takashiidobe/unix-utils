#include <stdio.h>
#include <stdlib.h>

#include "../lib/_init.h"

static const char *help = "Usage: cat [FILE]...\n"
                          "or: cat OPTION\n"
                          "Print the contents of a file(s).\n"
                          "\n"
                          "--help     display this help and exit\n"
                          "--version  output version information and exit";

static const char *version = "cat (libc) 0.0.1";

size_t min(size_t a, size_t b) { return a > b ? b : a; }

int main(int argc, char *argv[]) {
  if (_init((init_ops){
          .argc = argc, .argv = argv, .help = help, .version = version}) == 0)
    return 0;

  if (argc < 2) {
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    if (argc < 2) {
      while ((read = getline(&line, &len, stdin)) != -1) {
        printf("%s", line);
      }
      free(line);
      exit(0);
    }
  }

  char c;
  size_t file_count = min(argc - 1, FOPEN_MAX);
  FILE *files[file_count];

  for (size_t i = 0; i < file_count; i++) {
    FILE *fp = NULL;
    if (strcmp(argv[i + 1], "-") == 0) {
      fp = stdin;
    } else {
      fp = fopen(argv[i + 1], "r");
      if (fp == NULL) {
        exit(1);
      }
    }
    files[i] = fp;
  }

  for (size_t i = 0; i < file_count; i++) {
    while ((c = getc(files[i])) != EOF) {
      putchar(c);
    }
  }

  for (size_t i = 0; i < file_count; i++) {
    if (files[i] != stdin) {
      fclose(files[i]);
    }
  }

  exit(0);
}
