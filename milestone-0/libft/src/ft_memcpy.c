
#include "libft.h"

void *ft_memcpy(void *dest, const void *src, size_t n) {
  const uint8_t *src2;
  uint8_t *dest2;

  if (!dest && !src)
    return (dest);
  if (n != 0) {
    src2 = (const uint8_t *)src;
    dest2 = (uint8_t *)dest;
    while (n-- > 0)
      *dest2++ = *src2++;
  }
  return (dest);
}
