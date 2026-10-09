#include "../math/math.h"
#include "../types.h"
#include "net.h"
#include <arpa/inet.h>
#include <bits/types/struct_timeval.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <netinet/ip_icmp.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/types.h>

static void setup_inet(char egress_buf[], int buflen, uint16_t pid, int seq) {
  memset(egress_buf, 0, buflen);
  struct icmphdr *icmp = (struct icmphdr *)egress_buf;
  icmp->type = ICMP_ECHO;
  icmp->code = 0;
  icmp->un.echo.id = htons(pid);
  icmp->un.echo.sequence = htons(seq);
  icmp->checksum = 0;

  struct timeval *tv_send =
      (struct timeval *)(egress_buf + sizeof(struct icmphdr));
  gettimeofday(tv_send, NULL);

  icmp->checksum = calculate_checksum((unsigned short *)egress_buf, buflen);
}

static void recv_echo(int pid, int seq, int sock) {
  char recv_buf[1024];
  struct sockaddr_in reply_addr;
  socklen_t addr_len = sizeof(reply_addr);

  ssize_t bytes_recvd = recvfrom(sock, recv_buf, sizeof(recv_buf), 0,
                                 (struct sockaddr *)&reply_addr, &addr_len);

  if (bytes_recvd > 0) {
    struct timeval tv_recv;
    gettimeofday(&tv_recv, NULL);

    struct iphdr *ip = (struct iphdr *)recv_buf;
    int iphdr_len = ip->ihl * 4;

    struct icmphdr *reply_icmp = (struct icmphdr *)(recv_buf + iphdr_len);

    if (reply_icmp->type == ICMP_ECHOREPLY &&
        ntohs(reply_icmp->un.echo.id) == pid) {
      struct timeval sent_time;
      memcpy(&sent_time, recv_buf + iphdr_len + sizeof(struct icmphdr),
             sizeof(sent_time));
      // TODO: might need conditional compilation for 32/64 discrepancies here
      double rtt_ms = (tv_recv.tv_sec - sent_time.tv_sec) * 1000.0 +
                      (tv_recv.tv_usec - sent_time.tv_usec) / 1000.0;

      printf("%zd bytes from %s: icmp_seq=%d ttl=%d time=%.2f ms\n",
             bytes_recvd - iphdr_len, inet_ntoa(reply_addr.sin_addr),
             ntohs(reply_icmp->un.echo.sequence), ip->ttl, rtt_ms);
    }
  } else {
    printf("Request timeout for icmp_seq %d\n", seq);
  }
}

int ping_echo(uint16_t pid, int seq, int sock, struct sockaddr_in *target) {
  char egress_buf[PACKET_SIZE];
  setup_inet(egress_buf, sizeof(egress_buf), pid, seq);

  if (sendto(sock, egress_buf, sizeof(egress_buf), 0, (struct sockaddr *)target,
             sizeof(*target)) <= 0) {
    perror("sendto");
    return 1;
  }

  recv_echo(pid, seq, sock);

  return 0;
}
