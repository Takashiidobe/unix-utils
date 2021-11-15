#include <stdio.h>

// magic headers: `cffa edfe` = Mach-O 64-bit executable x86_64.
// magic headers; `cefa edfe` = Mach-O 32-bit executable x86_32.
// magic headers: `cafe babe` = java file.
// magic headers: `5351 4c69 7465 2066 6f72 6d61 7420 3300` = sqlite 3.
// gzip: `1F 8B 08`

int main(int argc, char** argv) {
  FILE* f = fopen(argv[1], "r");
  char c;
	int i = 0;

  while ((c = fgetc(f)) != EOF) {
		// figure out the file.
		printf("%02xn", c & 255);
		i++;
  }
  fclose(f);
}
