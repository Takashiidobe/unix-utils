#include <stdio.h>
#include <stdlib.h>

size_t min(size_t a, size_t b) { return a > b ? b : a; }

int main(int argc, char *argv[]) {
  char *line = NULL;
  size_t len = 0;
  ssize_t read;

  // TODO: implement ignoring signal.
  // signal(SIGINT, SIG_IGN);
  if (argc < 2) {
    while ((read = getline(&line, &len, stdin)) != -1) {
      printf("%s", line);
    }
    free(line);
    exit(0);
  }
  size_t file_count = min(argc, FOPEN_MAX);
  FILE *files[file_count];
  files[0] = stdout;

  for (size_t i = 1; i < file_count; i++) {
    FILE *fp = fopen(argv[i], "w+");
    if (fp == NULL) {
      exit(1);
    }
    files[i] = fp;
  }

  while ((read = getline(&line, &len, stdin)) != -1) {
    for (size_t i = 0; i < file_count; i++) {
      fputs(line, files[i]);
    }
  }
  free(line);

  for (size_t i = 1; i < file_count; i++) {
    fclose(files[i]);
  }

  exit(0);
}
