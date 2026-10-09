#ifndef TYPES_H
#define TYPES_H

#define PACKET_SIZE 64

#include <stddef.h>
#include <sys/stat.h>

typedef struct {
  int verbose;

  const char *address;
  const char *pname;
} CliOptions;

typedef struct {
  size_t transmitted; // Total ICMP echo reqs sent
  size_t received;    // Total valid ICMP echo replies received
  double tmin;        // Min RTT
  double tmax;        // Max RTT
  double tsum;        // Sum of RTTs
  double tsumsq;      // Sum of squares of RTTs
} PingStats;

#endif /* TYPES_H */
