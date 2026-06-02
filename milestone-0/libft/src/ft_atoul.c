
#include "libft.h"

unsigned long ft_atoul(const char *str) {
  unsigned long val;

  val = 0;
  while (ft_isspace(*str))
    str++;
  if (*str == '+')
    str++;
  while (ft_isdigit(*str))
    val = (val * 10) + (unsigned long)(*str++ - '0');
  return (val);
}
