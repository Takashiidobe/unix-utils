#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int copytoclipboard(const char *str) {

    const char proto_cmd[] = "echo '%s' | pbcopy";

    char cmd[strlen(str) + strlen(proto_cmd) - 1]; // -2 to remove the length of %s in proto cmd and + 1 for null terminator = -1
    sprintf(cmd, proto_cmd, str);

    return system(cmd);
}

int main(void) {
    copytoclipboard("copy this to clipboard");

    exit(0);
}
