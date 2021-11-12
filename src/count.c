#include <ctype.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  if (argc > 1) {
    printf("%d\n", argc - 1);
    return 0;
  }
  char buf[1] = {0};
  size_t count = 0;
  while (read(STDIN_FILENO, buf, sizeof(buf)) > 0) {
    while (read(STDIN_FILENO, buf, sizeof(buf)) > 0) {
      if (!isalnum(buf[0])) {
        count++;
      }
    }
  }
  printf("%zu\n", count);
}
