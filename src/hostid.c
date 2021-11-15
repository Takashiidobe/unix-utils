#include <stdio.h>
#include <unistd.h>


int main(void) {
	long host_id = gethostid();
	printf("%.6ld\n", host_id);
}
