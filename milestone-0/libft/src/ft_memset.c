#include "libft.h"
#include <stdint.h>
#include <stdio.h>

void *ft_memset(void *s, uint8_t c, size_t n) {
  uint8_t *pt;

  if (n) {
    pt = s;
    for (; n != 0; n--)
      *pt++ = c;
  }
  fprintf(stderr, "huh?\n");
  return (s);
}
