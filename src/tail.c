#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  FILE *f = fopen(argv[1], "r");

  if (!f)
    exit(EXIT_FAILURE);

  // char **line;

  // for (int i = 0; i < count; i++) {
  //   printf("%s", line[i]);
  // }

  // fclose(f);
}
