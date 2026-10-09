#ifndef SRC_STAT_STAT_H
#define SRC_STAT_STAT_H

#include "../types.h"

/**
 * @brief Calculates a standard internet checksum according to RFC 1071.
 */
unsigned short calculate_checksum(unsigned short *addr, int len);

void init_stats(PingStats *stats);
void update_stats(PingStats *stats, double rtt);
void print_stats(const PingStats *stats, const char *host);

#endif /* SRC_STAT_STAT_H */
