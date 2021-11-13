#include <stdio.h>
#include <fcntl.h>
#include <utime.h>

#define MAX_FILES 127

int main(int argc, char* argv[]) {
	for (unsigned i = 1; i < argc && i < MAX_FILES; i++) {
		open(argv[i], O_WRONLY|O_CREAT|O_NOCTTY|O_NONBLOCK, 0666);
		// update timestamp if file exists
		utime(argv[i], NULL);
	}
}
