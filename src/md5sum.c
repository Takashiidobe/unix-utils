#include "../lib/md5.h"

int main(int argc, char *argv[]) {
  MD5Result *res = md5((uint8_t *)argv[1], strlen(argv[1]));
  md5_print(res);
}
