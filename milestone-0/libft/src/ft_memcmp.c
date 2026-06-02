
#include "libft.h"

int ft_memcmp(const void *s1, const void *s2, size_t n) {
  uint8_t *se1;
  uint8_t *se2;
  size_t i;

  if (n == 0)
    return (0);
  se1 = (uint8_t *)s1;
  se2 = (uint8_t *)s2;
  i = 0;
  while (n--) {
    if (se1[i] != se2[i])
      return ((uint8_t)se1[i] - (uint8_t)se2[i]);
    i++;
  }
  return (0);
}
