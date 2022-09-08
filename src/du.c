#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

// du -> disk usage.
int main(int argc, char* argv[]) {
	// for all files in current dir, display their size in bytes and names.
	struct stat sb;
	if (lstat(argv[1], &sb) == -1) {
		perror("lstat");
		exit(EXIT_FAILURE);
	}

	size_t file_size = sb.st_blocks;
	if (file_size > 0) {
		file_size /= 2;
	}
	printf("%lu %s\n", file_size, argv[1]);
}
