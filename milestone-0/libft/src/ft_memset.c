
#include "libft.h"

void *ft_memset(void *s, uint8_t c, size_t n) {
  uint8_t *pt;

  if (n != 0) {
    pt = s;
    while (n != 0) {
      *pt++ = (uint8_t)c;
      n--;
    }
  }
  return (s);
}
