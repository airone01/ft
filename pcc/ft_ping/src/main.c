#include "cli/cli.h"
#include "net/net.h"
#include "stats/stats.h"
#include "types.h"
#include <netdb.h>
#include <netinet/in.h>
#include <netinet/ip_icmp.h>
#include <signal.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static volatile sig_atomic_t g_running = 1;

static void handle_sigint(int sig) {
  (void)sig;
  g_running = 0;
}

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

  struct timeval timeout = {.tv_sec = 2, .tv_usec = 0};
  int sock = prepare_sock(timeout);
  if (sock < 0) {
    perror("socket error (you might need to run as root)");
    freeaddrinfo(addr);
    return EXIT_FAILURE;
  }

  signal(SIGINT, handle_sigint);

  uint16_t pid = getpid() & 0xFFFF;
  int seq = 0;

  printf("PING %s (%s): %lu data bytes", opts.address, ip_str,
         PACKET_SIZE - sizeof(struct icmphdr));
  if (opts.verbose)
    printf(", id 0x%04x = %u", pid, pid);
  printf("\n");

  PingStats stats;
  init_stats(&stats);

  while (g_running) {
    if (send_echo(sock, pid, seq, target, &stats) < 0)
      break;

    int res = recv_echo_loop(sock, pid, opts, &stats);
    if (res == -2 || !g_running)
      // Caught SIGINT
      break;

    seq++;
    if (res == 0 && g_running)
      sleep(1);
  }

  print_stats(&stats, opts.address);

  freeaddrinfo(addr);
  close(sock);
  return 0;
}
