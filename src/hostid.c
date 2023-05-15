#include <stdio.h>
#include <unistd.h>

int main(void) {
#ifndef __ANDROID__
	long host_id = gethostid();
	printf("%.6ld\n", host_id);
#endif
  return 0;
}
