#include <stdio.h>
#include <unistd.h>
#include <pwd.h>

int main(void) {
	 uid_t uid = geteuid();
  struct passwd *pw = getpwuid(uid);
  if (pw) {
    printf("%s\n", pw->pw_name);
    printf("%s\n", pw->pw_shell);
    printf("%s\n", pw->pw_name);
	}

  return 0;
}
