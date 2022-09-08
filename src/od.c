#include <stdio.h>

int main(int argc, char** argv) {
  FILE* f = fopen(argv[1], "r");
  char c;
  int i = 0;
	int j = 0;
	int k = 0;

  while ((c = fgetc(f)) != EOF && k < 64) {
		// newline every 16
		if (i > 0 && i % 16 == 0) {
			puts("");
		}
		// new space every two chars
		if (j > 0 && j % 2 == 0 && j % 16 != 0) {
			printf(" ");
		}
    printf("%o", c & 255);
		i++;
		j++;
		k++;
  }
  fclose(f);
}
