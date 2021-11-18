#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[]) {
	// take a file.
	FILE* f = fopen(argv[1], "r");
	if (f == NULL) {
		return 1;
	}

	char *line = NULL;
  size_t len = 0;
  ssize_t nread;
  size_t count = 1;

	// skip newlines.

  for (int index = 1; index < argc; index++) {
    FILE *fp = fopen(argv[index], "r");
    while ((nread = getline(&line, &len, fp)) != -1) {
			if (!strcmp(line, "\n")) {
				printf("    %s", line);
				continue;
			}
      printf("    %lu %s", count, line);
      count++;
    }
    puts("");
    fclose(fp);
  }

  free(line);

  return 0;
}

