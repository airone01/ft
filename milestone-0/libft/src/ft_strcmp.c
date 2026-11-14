#include "libft.h"
#include <stdint.h>

int ft_strcmp(const char *s1, const char *s2) {
  return (ft_strncmp(s1, s2, SIZE_MAX));
}
