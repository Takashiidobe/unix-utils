#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#ifdef __linux__
#include <linux/unistd.h>
#include <sys/sysinfo.h>

long get_uptime()
{
    struct sysinfo s_info;
    int error = sysinfo(&s_info);
    if (error != 0)
			exit(1);
    return s_info.uptime;
}
#endif

#ifdef __APPLE__
#define _DARWIN_C_SOURCE
#include <sys/sysctl.h>
#include <time.h>

long get_uptime() {
  struct timeval boottime;
  size_t len = sizeof(boottime);
  int mib[2] = {CTL_KERN, KERN_BOOTTIME};
  if (sysctl(mib, 2, &boottime, &len, NULL, 0) < 0)
    exit(1);
  time_t bsec = boottime.tv_sec;
  time_t csec = time(NULL);
  return difftime(csec, bsec) / 86400;
}
#endif

int main(void) {
	printf("%lu days.\n", get_uptime());
}
