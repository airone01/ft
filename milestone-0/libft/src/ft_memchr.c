
#include "libft.h"

void *ft_memchr(const void *s, uint8_t c, size_t n) {
  uint8_t *se;

  if (!s)
    return (NULL);
  se = (uint8_t *)s;
  while (n--) {
    if (*se == (uint8_t)c)
      return (se);
    se++;
  }
  return (0);
}
