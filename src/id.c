#include <stdio.h>
#include <unistd.h>

int main(void) {
	// group_id
	gid_t group_id = getgid();
	printf("group_id: %d\n", group_id);
	// user_id
	uid_t user_id = getuid();
	printf("user_id: %d\n", user_id);
}
