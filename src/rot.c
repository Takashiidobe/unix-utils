#include "../lib/getopt.h"
#include <stdio.h>
#include <stdlib.h>

#include "../lib/_init.h"

static size_t rot = 13;

static const char *help = "Usage: rot\n"
                          "or: rot OPTION\n"
                          "Rotate characters of file using ROT 13.\n"
                          "\n"
                          "--help     display this help and exit\n"
                          "--version  output version information and exit";

static const char *version = "rot (libc) 0.0.1";

static void line_to_rot(char *line, size_t len, size_t rot) {
  for (size_t i = 0; i < len; i++) {
    if (line[i] >= 'A' && line[i] <= 'Z') {
      line[i] -= 'A';
      line[i] += rot;
      line[i] %= 26;
      line[i] += 'A';
    } else if (line[i] >= 'a' && line[i] <= 'z') {
      line[i] -= 'a';
      line[i] += rot;
      line[i] %= 26;
      line[i] += 'a';
    }
  }
}

static struct option long_options[] = {{"rotate", optional_argument, 0, 'r'},
                                       {0, 0, 0, 0}};

int main(int argc, char *argv[]) {
  if (util_setup((init_ops){
          .argc = argc, .argv = argv, .help = help, .version = version}) == 0)
    return 0;

  char *line = NULL;
  size_t len = 0;
  ssize_t read;
  if (argc < 2) {
    while ((read = getline(&line, &len, stdin)) != -1) {
      line_to_rot(line, len, rot);
      printf("%s", line);
    }
    free(line);
    exit(0);
  }

  int c;

  while (1) {
    int option_index = 0;

    c = getopt_long(argc, argv, ":r:", long_options, &option_index);

    if (c == -1)
      break;

    switch (c) {
    case 'r':
      rot = atoi(optarg) % 26;
      break;
    case '?':
      abort();
    default:
      abort();
    }
  }

  for (size_t i = optind; i < argc; i++) {
    if (strcmp("-", argv[i]) == 0) {
      while ((read = getline(&line, &len, stdin)) != -1) {
        line_to_rot(line, len, rot);
        printf("%s", line);
      }
    }
    FILE *fp = fopen(argv[i], "r");
    if (fp == NULL) {
      perror("fopen");
      exit(1);
    }

    printf("===> %s <===\n", argv[i]);

    while ((read = getline(&line, &len, fp)) != -1) {
      line_to_rot(line, len, rot);
      printf("%s", line);
    }
    fclose(fp);
  }
  free(line);

  return 0;
}
