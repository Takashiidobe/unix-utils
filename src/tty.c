#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
  char* tty = ttyname(STDIN_FILENO);

  if (tty)
    puts(tty);
  else
    puts("not a tty");

  exit(isatty(STDIN_FILENO) ? EXIT_SUCCESS : 1);
}
