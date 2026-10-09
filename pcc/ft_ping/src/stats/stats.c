#include "stats.h"
#include <float.h>
#include <math.h>
#include <stdio.h>

void init_stats(PingStats *stats) {
  stats->transmitted = 0;
  stats->received = 0;
  stats->tmin = DBL_MAX;
  stats->tmax = 0.0;
  stats->tsum = 0.0;
  stats->tsumsq = 0.0;
}

void update_stats(PingStats *stats, double rtt) {
  stats->received++;
  stats->tsum += rtt;
  stats->tsumsq += rtt * rtt;
  if (rtt < stats->tmin)
    stats->tmin = rtt;
  if (rtt > stats->tmax)
    stats->tmax = rtt;
}

void print_stats(const PingStats *stats, const char *host) {
  printf("--- %s ping statistics ---\n", host);

  long loss = 0;
  if (stats->transmitted > 0)
    loss = (long)(((stats->transmitted - stats->received) * 100) /
                  stats->transmitted);

  printf("%zu packets transmitted, %zu packets received, %ld%% packet loss\n",
         stats->transmitted, stats->received, loss);

  if (stats->received > 0) {
    double avg = stats->tsum / (double)stats->received;
    double variance = (stats->tsumsq / (double)stats->received) - (avg * avg);
    double stddev = sqrt(variance > 0.0 ? variance : 0.0);

    printf("rtt min/avg/max/stddev = %.3f/%.3f/%.3f/%.3f ms\n", stats->tmin,
           avg, stats->tmax, stddev);
  }
}
