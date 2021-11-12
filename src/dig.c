#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>

#include "../lib/_init.h"

static const char *help = "dig - DNS lookup utility\n"
                          "dig is used to query DNS servers for lookups";

static const char *version = "dig (libc) 0.0.1";

int main(int argc, char *argv[]) {
  struct addrinfo hints, *res, *res0;
  char host[NI_MAXHOST];

  if (_init((init_ops){.argc = argc,
                       .argv = argv,
                       .help = help,
                       .version = version,
                       .print_help_by_default = 1}) == 0)
    return 0;

  memset(&hints, 0, sizeof hints);
  hints.ai_family = PF_UNSPEC;
  hints.ai_socktype = SOCK_DGRAM;

  int error = getaddrinfo(argv[1], NULL, &hints, &res0);
  if (error) {
    fprintf(stderr, "%s\n", gai_strerror(error));
    exit(1);
  }

  for (res = res0; res; res = res->ai_next) {
    error = getnameinfo(res->ai_addr, res->ai_addrlen, host, sizeof host, NULL,
                        0, NI_NUMERICHOST);

    if (error) {
      fprintf(stderr, "%s\n", gai_strerror(error));
    } else {
      printf("%s\n", host);
    }
  }

  freeaddrinfo(res0);

  return 0;
}
