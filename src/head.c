#include "../lib/getopt.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  char *line = NULL;
  size_t len = 0;
  ssize_t nread;
  int line_count = 10;

  struct option long_options[] = {{"lines", required_argument, 0, 'n'},
                                  {0, 0, 0, 0}};

  while (1) {
    int option_index = 0;

    int c = getopt_long(argc, argv, ":n:q:0", long_options, &option_index);

    if (c == -1)
      break;

    switch (c) {
    case 'n':
      line_count = atoi(optarg);
      break;

    case '?':
      printf("head: invalid option -- '%s'\n"
             "Try 'head --help' for more information.\n",
             argv[optind - 1]);
      exit(1);

    default:
      exit(1);
    }
  }

  for (int index = optind; index < argc; index++) {
    FILE *fp = fopen(argv[index], "r");
    size_t count = 0;
    printf("===> %s <===\n", argv[index]);
    while ((nread = getline(&line, &len, fp)) != -1 && count < line_count) {
      printf("%s", line);
      count++;
    }
    puts("");
    fclose(fp);
  }

  free(line);

  return 0;
}
