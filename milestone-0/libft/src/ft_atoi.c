
#include "libft.h"

int ft_atoi(const char *str) {
  long val;

  val = ft_atol(str);
  if (val > INT_MAX || val < INT_MIN)
    return (0);
  return ((int)val);
}
