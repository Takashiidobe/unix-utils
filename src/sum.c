#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../lib/_init.h"

static const char *help = "Usage: sum [FILE]...\n"
                          "or: sum OPTION\n"
                          "Exit with a status code indicating success.\n"
                          "\n"
                          "--help     display this help and exit\n"
                          "--version  output version information and exit";

static const char *version = "sum (libc) 0.0.1";

size_t min(size_t a, size_t b) { return a > b ? b : a; }

// TODO: move to crypto/sum?
// uint16_t sum(const char *s) {
//   int checksum = 0;
//   size_t len = strlen(s);
//
//   for (int i = 0; i < len; i++) {
//     checksum = (checksum >> 1) + ((checksum & 1) << 15);
//     checksum += s[i];
//     checksum &= 0xffff;
//   }
//   return checksum;
// }

void bsd_sum(char c, uint16_t *checksum, size_t *total_bytes) {
  *total_bytes = *total_bytes + 1;
  *checksum = (*checksum >> 1) + ((*checksum & 1) << 15);
  *checksum += c;
  *checksum &= 0xffff;
}

int main(int argc, char *argv[]) {
  if (_init((init_ops){
          .argc = argc, .argv = argv, .help = help, .version = version}) == 0)
    return 0;

  uint16_t checksum = 0;
  size_t total_bytes = 0;

  char c;

  if (argc < 2) {
    while ((c = getc(stdin)) != EOF) {
      bsd_sum(c, &checksum, &total_bytes);
    }
    printf("%d\n", checksum);
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
    while ((c = getc(files[i])) != EOF) {
      bsd_sum(c, &checksum, &total_bytes);
    }
    size_t formatted_bytes = total_bytes / 512;
    formatted_bytes = formatted_bytes == 0 ? 1 : formatted_bytes;

    printf("%d %zu %s\n", checksum, formatted_bytes, argv[i + 1]);
    checksum = 0;
    total_bytes = 0;
  }

  for (size_t i = 0; i < file_count; i++) {
    if (files[i] != stdin) {
      fclose(files[i]);
    }
  }

  exit(0);
}
