#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

/*
S_ISUID  (04000)
       set-user-ID (set process effective user ID on execve(2))

S_ISGID  (02000)
       set-group-ID (set process effective group ID on execve(2);
       mandatory locking, as described in fcntl(2); take a new
       file's group from parent directory, as described in
       chown(2) and mkdir(2))

S_ISVTX  (01000)
       sticky bit (restricted deletion flag, as described in
       unlink(2))

S_IRUSR  (00400)
       read by owner

S_IWUSR  (00200)
       write by owner

S_IXUSR  (00100)
       execute/search by owner ("search" applies for directories,
       and means that entries within the directory can be
       accessed)

S_IRGRP  (00040)
       read by group

S_IWGRP  (00020)
       write by group

S_IXGRP  (00010)
       execute/search by group

S_IROTH  (00004)
       read by others

S_IWOTH  (00002)
       write by others

S_IXOTH (00001)
       execute/search by others
*/

#define MAX_ARGS 127

enum Permissions {
  P_NONE = 0,
  P_EXECUTE = 1,
  P_WRITE = 2,
  P_READ = 4,
};

enum Operations { O_SUB = 1, O_ADD = 2, O_EQUAL = 4 };

enum Users {
  U_FILE_OWNER = 1,
  U_GROUP_MEMBER = 2,
  U_OTHERS = 4,
	U_ALL = 7,
};

struct Action {
  unsigned users ;
  unsigned operations ;
  unsigned permissions ;
};

void add_permission(int* mode, int permission) {
	*mode |= permission;
}

void remove_permission(int* mode, int permission) {
	*mode -= permission;
}

int main(int argc, char* argv[]) {
  int mode = atoi(argv[1]);

  // correctly set mode, apply to all files.
  if (mode > 0) {
    goto apply;
  }

  // parse through the first argument properly.
  size_t len = strlen(argv[1]);
  struct Action action = {.users = 0, .operations = 0, .permissions = 0};
  for (int i = 0; i < len; i++) {
    switch (argv[1][i]) {
      case '+':
	action.operations |= O_ADD;
	break;
      case '-':
	action.operations |= O_SUB;
	break;
      case '=':
	action.operations |= O_EQUAL;
	break;
      case 'r':
	action.permissions |= P_READ;
	break;
      case 'w':
	action.permissions |= P_WRITE;
	break;
      case 'x':
	action.permissions |= P_EXECUTE;
	break;
      case 'u':
	action.users |= U_FILE_OWNER;
	break;
      case 'g':
	action.users |= U_GROUP_MEMBER;
	break;
      case 'o':
	action.users |= U_OTHERS;
	break;
      case 'a':
	action.users |= U_ALL;
	break;
      default:
	break;
    }
  }

	// if no group is set, set to all.
	if (action.users == 0) {
		action.users = U_ALL;
	}

	// otherwise, apply to u g or o.
	if (action.operations & O_ADD) {
		if (action.users & U_FILE_OWNER) {
			add_permission(&mode, S_IRUSR);
		}
		if (action.users & U_GROUP_MEMBER) {
			add_permission(&mode, S_IRGRP);
		}
		if (action.users & U_OTHERS) {
			add_permission(&mode, S_IROTH);
		}
		if (action.permissions & P_WRITE) {
			if (action.users & U_FILE_OWNER) {
				add_permission(&mode, S_IWUSR);
			}
			if (action.users & U_GROUP_MEMBER) {
				add_permission(&mode, S_IWGRP);
			}
			if (action.users & U_OTHERS) {
				add_permission(&mode, S_IWOTH);
			}
		}
		if (action.permissions & P_EXECUTE) {
			if (action.users & U_FILE_OWNER) {
				add_permission(&mode, S_IRUSR);
			}
			if (action.users & U_FILE_OWNER) {
				add_permission(&mode, S_IXGRP);
			}
			if (action.users & U_FILE_OWNER) {
				add_permission(&mode, S_IXOTH);
			}
		}
	} else if (action.operations & O_SUB) {
		// remove permissions
	} else if (action.operations & O_EQUAL) {

	}

apply:
  for (unsigned i = 2; i < argc && i < MAX_ARGS; i++) {
		// get the current mode of the file then xor it for mode
		int prev_permissions = 0;
		printf("prev permissions: %d\n", prev_permissions);
    // chmod(argv[i], mode);
  }
  exit(0);
}
