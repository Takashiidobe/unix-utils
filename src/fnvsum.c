#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../lib/_init.h"

static const char *help = "Usage: fnvsum [FILE]...\n"
                          "or: fnvsum OPTION\n"
                          "Print an fnv hash of input.\n"
                          "\n"
                          "--help     display this help and exit\n"
                          "--version  output version information and exit";

static const char *version = "fnvsum (libc) 0.0.1";

size_t min(size_t a, size_t b) { return a > b ? b : a; }

#define FNV_PRIME_32 16777619
#define FNV_OFFSET_32 2166136261U

void _fnv(char c, uint32_t *hash) {
  *hash = *hash ^ c;
  *hash = *hash * FNV_PRIME_32;
}

int main(int argc, char *argv[]) {
  if (_init((init_ops){
          .argc = argc, .argv = argv, .help = help, .version = version}) == 0)
    return 0;

  uint32_t hash = FNV_OFFSET_32;

  char c;

  if (argc < 2) {
    while ((c = getc(stdin)) != EOF) {
      _fnv(c, &hash);
    }
    printf("%u\n", hash);
    exit(0);
  }

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
    hash = FNV_OFFSET_32;
    while ((c = getc(files[i])) != EOF) {
      _fnv(c, &hash);
    }
    printf("%u\n", hash);
  }

  for (size_t i = 0; i < file_count; i++) {
    if (files[i] != stdin) {
      fclose(files[i]);
    }
  }

  exit(0);
}
