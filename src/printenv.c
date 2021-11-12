#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern char **environ;

int main(int argc, char *argv[]) {
  const char s[] = "=";
  int found = 0;

  if (argc > 1) {
    for (size_t i = 1; i < argc; i++) {
      char *arg = strdup(argv[i]);
      for (size_t i = 0; environ[i] != NULL; i++) {
        char *env = strdup(environ[i]);

        char *token;

        strtok_r(env, s, &token);

        if (strcmp(env, arg) == 0) {
          printf("%s\n", token);
          found = 1;
        }
      }
    }
    found ? exit(0) : exit(1);
  }

  for (size_t i = 0; environ[i] != NULL; i++) {
    puts(environ[i]);
  }

  exit(0);
}
