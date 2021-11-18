#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
  int status;
  if (wait(&status) >= 0) {
    if (status) {
      printf("Child process exited with %d status\n", WEXITSTATUS(status));
    }
  }
}
