#include "../lib/md5.h"

#define MAX_LEN 128

int main(int argc, char *argv[]) {
	MD5Result out;
	if (argc > 1) {
		if (strlen(argv[1]) > (MAX_LEN - 2)) {
			fprintf(stderr, "%s was too long to hash with md5.", argv[1]);
			exit(1);
		}
		char copy[MAX_LEN + 2];
		strcpy(copy, argv[1]);
		copy[strlen(argv[1])] = '\n';
		copy[strlen(argv[1]) + 1] = '\0';
		md5((uint8_t *)copy, strlen(copy), &out);
		md5_print(&out);
	} else {
		char *line = NULL;
		size_t len = 0;
		ssize_t read;

		while ((read = getline(&line, &len, stdin)) != -1) {
			md5((uint8_t *)line, strlen(line), &out);
			md5_print(&out);
		}
		free(line);
	}
	exit(0);
}
