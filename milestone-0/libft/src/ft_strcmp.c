
#include "libft.h"
#include <limits.h>

int ft_strcmp(const char *s1, const char *s2) {
  return (ft_strncmp(s1, s2, ULLONG_MAX));
}
