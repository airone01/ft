
#include "libft.h"

void *ft_memmove(void *dest, const void *src, size_t n) {
  const uint8_t *src2;
  uint8_t *dest2;

  if (!dest && !src)
    return (dest);
  if (n == 0)
    return (dest);
  src2 = src;
  dest2 = dest;
  if ((dest2 > src2) && (dest2 < src2 + n)) {
    dest2 += n;
    src2 += n;
    while (n--)
      *--dest2 = *--src2;
    return (dest);
  }
  return (ft_memcpy(dest, src, n));
}
