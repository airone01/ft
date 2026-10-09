#include "net.h"
#include <arpa/inet.h>
#include <bits/types/struct_timeval.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>

int resolve_host(const CliOptions opts, struct sockaddr_in **target,
                 struct addrinfo **res, char ip_str[], int ipnmemb) {
  if (!res)
    return 1;

  struct addrinfo hints;
  memset(&hints, 0, sizeof(hints));
  hints.ai_family = AF_INET;    // IPv4 only
  hints.ai_socktype = SOCK_RAW; // Privileged raw sock only

  int ret = getaddrinfo(opts.address, NULL, &hints, res);
  if (ret != 0) {
    fprintf(stderr, "%s: unknown host: %s\n", opts.pname, gai_strerror(ret));
    return 2;
  }

  *target = (struct sockaddr_in *)(*res)->ai_addr;
  inet_ntop(AF_INET, &((*target)->sin_addr), ip_str, INET_ADDRSTRLEN);

  return 0;
}

int prepare_sock(struct timeval timeout) {
  int sock = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
  if (sock < 0)
    return sock;

  setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout));

  return sock;
}
