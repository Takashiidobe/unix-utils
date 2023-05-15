#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
  int status;
#ifndef __ANDROID__
  if (wait(&status) >= 0) {
    if (status) {
      printf("Child process exited with %d status\n", WEXITSTATUS(status));
    }
  }
#endif
}
