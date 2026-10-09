#include "stats.h"

unsigned short calculate_checksum(unsigned short *addr, int len) {
  int nleft = len;
  int sum = 0;
  unsigned short *w = addr;
  unsigned short answer = 0;

  while (nleft > 1) {
    sum += *w++;
    nleft -= 2;
  }
  if (nleft == 1) {
    *(unsigned char *)(&answer) = *(unsigned char *)w;
    sum += answer;
  }
  sum = (sum >> 16) + (sum & 0xffff);
  sum += (sum >> 16);
  return ~sum;
}

/* In case we're not allowed to use libm */

// static double nabs(double a) { return (a < 0) ? -a : a; }
//
// static double nsqrt(double a, double prec) {
//   if (a <= 0.0 || a < prec)
//     return 0.0;
//   double x0, x1 = a / 2.0;
//   do {
//     x0 = x1;
//     x1 = (x0 + a / x0) / 2.0;
//   } while (nabs(x1 - x0) > prec);
//   return x1;
// }
