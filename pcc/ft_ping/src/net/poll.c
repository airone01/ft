#include "net.h"
#include <errno.h>
#include <poll.h>
#include <sys/poll.h>
#include <sys/time.h>

// TODO: might need conditional compilation for 32/64 discrepancies here
static long get_time_ms(void) {
  struct timeval tv;
  gettimeofday(&tv, NULL);
  return (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
}

int recv_echo_loop(int sock, uint16_t pid, const CliOptions opts,
                   PingStats *stats) {
  long start_ms = get_time_ms();
  long timeout_ms = 1000;

  while (1) {
    long elapsed = get_time_ms() - start_ms;
    long remaining = timeout_ms - elapsed;
    if (remaining <= 0)
      return -1;

    struct pollfd pfd = {.fd = sock, .events = POLLIN};
    int ret = poll(&pfd, 1, (int)remaining);

    if (ret < 0) {
      if (errno == EINTR)
        return -2; // SIGINT
      return -1;
    }
    if (ret == 0)
      return -1;

    char buf[1024];
    struct sockaddr_in from;
    socklen_t from_len = sizeof(from);

    ssize_t bytes = recvfrom(sock, buf, sizeof(buf), MSG_DONTWAIT,
                             (struct sockaddr *)&from, &from_len);
    if (bytes <= 0)
      continue;

    int parse_res = process_packet(buf, bytes, pid, &from, opts, stats);
    if (parse_res == 0)
      return 0; // valid echo reply
    else if (parse_res == 1)
      return 1; // relevant ICMP error
    // parse_res == 2 means packet belong to another process, continuing.
  }
}
