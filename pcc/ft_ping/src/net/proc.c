#include "../stats/stats.h"
#include "../types.h"
#include "net.h"
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <netinet/ip_icmp.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/types.h>

static void print_verbose_ip_dump(struct iphdr *orig_ip,
                                  struct icmphdr *orig_icmp) {
  unsigned char *raw = (unsigned char *)orig_ip;
  char s_str[INET_ADDRSTRLEN], d_str[INET_ADDRSTRLEN];

  inet_ntop(AF_INET, &orig_ip->saddr, s_str, sizeof(s_str));
  inet_ntop(AF_INET, &orig_ip->daddr, d_str, sizeof(d_str));

  printf("IP Hdr Dump:\n ");
  for (size_t i = 0; i < sizeof(struct iphdr); i++)
    printf("%02x%s", raw[i], (i % 2) ? " " : "");

  printf("\nVr HL TOS  Len   ID Flg  off TTL Pro  cks      Src\tDst\tData\n");
  printf(" %1x  %1x  %02x %04x %04x   %1x %04x  %02x  %02x %04x %s  %s\n",
         orig_ip->version, orig_ip->ihl, orig_ip->tos, ntohs(orig_ip->tot_len),
         ntohs(orig_ip->id), (ntohs(orig_ip->frag_off) & 0xe000) >> 13,
         ntohs(orig_ip->frag_off) & 0x1fff, orig_ip->ttl, orig_ip->protocol,
         ntohs(orig_ip->check), s_str, d_str);

  int orig_ip_len = orig_ip->ihl * 4;
  int icmp_size = ntohs(orig_ip->tot_len) - orig_ip_len;

  printf("ICMP: type %d, code %d, size %d, id 0x%04x, seq 0x%04x\n",
         orig_icmp->type, orig_icmp->code, icmp_size,
         ntohs(orig_icmp->un.echo.id), ntohs(orig_icmp->un.echo.sequence));
}

// 0: matching ICMP_ECHOREPLY
// 1: matching ICMP Error (timeout, unreachable)
// 2: irrelevant packet
int process_packet(char *buf, ssize_t len, uint16_t pid,
                   struct sockaddr_in *from, const CliOptions opts,
                   PingStats *stats) {
  if (len < (ssize_t)sizeof(struct iphdr))
    return 2;

  struct iphdr *ip = (struct iphdr *)buf;
  int ip_hdr_len = ip->ihl * 4;

  if (ip_hdr_len < 20 || len < (ssize_t)(ip_hdr_len + sizeof(struct icmphdr)))
    return 2;

  struct icmphdr *icmp = (struct icmphdr *)(buf + ip_hdr_len);
  ssize_t icmp_len = len - ip_hdr_len;

  // Standard ICMP echo reply
  if (icmp->type == ICMP_ECHOREPLY) {
    uint16_t recv_id = ntohs(icmp->un.echo.id);
    if (recv_id != pid)
      return 2;

    uint16_t seq = ntohs(icmp->un.echo.sequence);

    if (icmp_len >=
        (ssize_t)(sizeof(struct icmphdr) + sizeof(struct timeval))) {
      struct timeval tv_recv, tv_send;
      gettimeofday(&tv_recv, NULL);

      // Safe align copy
      memcpy(&tv_send, buf + ip_hdr_len + sizeof(struct icmphdr),
             sizeof(tv_send));

      double rtt = (tv_recv.tv_sec - tv_send.tv_sec) * 1000.0 +
                   (tv_recv.tv_usec - tv_send.tv_usec) / 1000.0;

      update_stats(stats, rtt);

      printf("%zd bytes from %s: icmp_seq=%u ttl=%d time=%.3f ms\n", icmp_len,
             inet_ntoa(from->sin_addr), seq, ip->ttl, rtt);
    } else {
      printf("%zd bytes from %s: icmp_seq=%u ttl=%d\n", icmp_len,
             inet_ntoa(from->sin_addr), seq, ip->ttl);
    }
    return 0;
  }

  // ICMP error packet
  if (icmp->type == ICMP_TIME_EXCEEDED || icmp->type == ICMP_DEST_UNREACH) {
    ssize_t min_err_len = ip_hdr_len + sizeof(struct icmphdr) +
                          sizeof(struct iphdr) + sizeof(struct icmphdr);

    if (len < min_err_len)
      return 2; // Whatever the fuck this is

    struct iphdr *orig_ip =
        (struct iphdr *)(buf + ip_hdr_len + sizeof(struct icmphdr));
    int orig_ip_len = orig_ip->ihl * 4;

    if (len < (ssize_t)(ip_hdr_len + sizeof(struct icmphdr) + orig_ip_len + 8))
      return 2;

    struct icmphdr *orig_icmp =
        (struct icmphdr *)(buf + ip_hdr_len + sizeof(struct icmphdr) +
                           orig_ip_len);

    if (orig_icmp->type != ICMP_ECHO || ntohs(orig_icmp->un.echo.id) != pid)
      return 2; // Error wasn't triggered by our echo request

    if (icmp->type == ICMP_TIME_EXCEEDED) {
      if (icmp->code == ICMP_EXC_TTL)
        printf("%zd bytes from %s: Time to live exceeded\n", icmp_len,
               inet_ntoa(from->sin_addr));
      else
        printf("%zd bytes from %s: Time exceeded, code: %d\n", icmp_len,
               inet_ntoa(from->sin_addr), icmp->code);
    } else if (icmp->type == ICMP_DEST_UNREACH) {
      printf("%zd bytes from %s: Destination Host Unreachable\n", icmp_len,
             inet_ntoa(from->sin_addr));
    }

    if (opts.verbose)
      print_verbose_ip_dump(orig_ip, orig_icmp);
    return 1;
  }

  return 2;
}
