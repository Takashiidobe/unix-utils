#include <stdio.h>

int main(int argc, char* argv[]) {
  if (argc != 3) {
    return 1;
  }

  // if the files are the same, no output.
  FILE* f1 = fopen(argv[1], "r");
  FILE* f2 = fopen(argv[2], "r");

	char c1, c2;

	int line_number = 1;
	int char_number = 1;

  while ((c1 = fgetc(f1)) != EOF && (c2 = fgetc(f2)) != EOF) {
		if (c1 != c2) {
			printf("%s %s differ: char %d, line %d\n", argv[1], argv[2], char_number, line_number);
			return 1;
		}
		char_number++;
		if (c1 == '\n' && c2 == '\n') {
			line_number++;
			char_number = 1;
		}
  }

  return 0;
}
