#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
	if (argc < 3) {
		fprintf(stderr, "You must provide 3 arguments for %s", argv[0]);
		exit(1);
	}
	rename(argv[1], argv[2]);
}
