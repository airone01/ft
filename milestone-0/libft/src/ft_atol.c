
#include "libft.h"

long ft_atol(const char *str) {
  long val;
  bool neg;

  val = 0;
  neg = false;
  while (ft_isspace(*str))
    str++;
  if (*str == '+' || *str == '-') {
    if (*str == '-')
      neg = true;
    str++;
  }
  while (ft_isdigit(*str))
    val = (val * 10) + (*str++ - '0');
  if (neg)
    val = -val;
  return (val);
}
