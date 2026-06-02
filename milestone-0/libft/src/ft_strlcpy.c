
#include "libft.h"

size_t ft_strlcpy(char *dst, const char *src, size_t size) {
  const char *src_start = src;

  if (size > 0) {
    while (--size > 0 && *src) {
      *dst++ = *src++;
    }
    *dst = '\0';
  }
  while (*src)
    src++;
  return ((unsigned long)(src - src_start));
}
