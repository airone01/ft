#include "cli/cli.h"
#include "net/net.h"
#include "types.h"
#include <netdb.h>
#include <netinet/in.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, const char *argv[]) {
  CliOptions opts;

  int rparse = parse_args(argc, argv, &opts);
  if (rparse == -1)
    return EXIT_FAILURE;
  if (rparse == -2)
    return EXIT_SUCCESS;

  struct addrinfo *addr;
  struct sockaddr_in *target;
  char ip_str[INET_ADDRSTRLEN];
  if (resolve_host(opts, &target, &addr, ip_str, INET_ADDRSTRLEN) != 0)
    return EXIT_FAILURE;

  printf("PING %s (%s): %d data bytes\n", opts.address, ip_str, PACKET_SIZE);

  struct timeval timeout = {.tv_sec = 2, .tv_usec = 0};
  int sock = prepare_sock(timeout);
  if (sock < 0) {
    perror("socket error (you might need to run as root)");
    freeaddrinfo(addr);
    return EXIT_FAILURE;
  }

  uint16_t pid = getpid() & 0xFFFF;
  int seq = 1;

  while (1) {
    if (ping_echo(pid, seq, sock, target) != 0)
      break;

    seq++;
    sleep(1);
  }

  freeaddrinfo(addr);
  close(sock);
  return 0;
}
