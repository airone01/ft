#include "../stats/stats.h"
#include "net.h"
#include <netinet/in.h>
#include <netinet/ip_icmp.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/types.h>

int send_echo(int sock, uint16_t pid, int seq, struct sockaddr_in *target,
              PingStats *stats) {
  char egress_buf[PACKET_SIZE];
  memset(egress_buf, 0, sizeof(egress_buf));

  struct icmphdr *icmp = (struct icmphdr *)egress_buf;
  icmp->type = ICMP_ECHO;
  icmp->code = 0;
  icmp->un.echo.id = htons(pid);
  icmp->un.echo.sequence = htons(seq);
  icmp->checksum = 0;

  struct timeval tv_send;
  gettimeofday(&tv_send, NULL);
  memcpy(egress_buf + sizeof(struct icmphdr), &tv_send, sizeof(tv_send));

  icmp->checksum =
      calculate_checksum((unsigned short *)egress_buf, sizeof(egress_buf));

  stats->transmitted++;
  ssize_t sent = sendto(sock, egress_buf, sizeof(egress_buf), 0,
                        (struct sockaddr *)target, sizeof(*target));
  if (sent < 0) {
    perror("sendto");
    return -1;
  }
  return 0;
}
