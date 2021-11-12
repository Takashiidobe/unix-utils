#include <errno.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
  if (argc < 2) {
    printf("Please provide one argument for the myseq command.");
    return 1;
  }

  uintmax_t num = strtoumax(argv[1], NULL, 10);
  if (num == UINTMAX_MAX && errno == ERANGE) {
    printf("The number provided could not be parsed.");
    return 3;
  }

  for (size_t i = 1; i <= num; i++) {
    printf("%zu\n", i);
  }

  if (argc > 2) {
    printf("Please provide only one argument for the myseq command.");
    return 2;
  }
}
