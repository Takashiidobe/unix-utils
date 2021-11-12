#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/sysctl.h>
#include <time.h>

int main(void) {
  struct timeval boottime;
  size_t len = sizeof(boottime);
  int mib[2] = {CTL_KERN, KERN_BOOTTIME};
  if (sysctl(mib, 2, &boottime, &len, NULL, 0) < 0)
    exit(1);
  time_t bsec = boottime.tv_sec;
  time_t csec = time(NULL);
  printf("%f days.\n", difftime(csec, bsec) / 86400);
}
