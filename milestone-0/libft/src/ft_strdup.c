
#include "libft.h"

char *ft_strdup(const char *s) {
  size_t i;
  char *dst;

  dst = ft_calloc(ft_strlen(s) + 1, sizeof(char));
  if (!dst)
    return (0);
  i = 0;
  while (s[i]) {
    dst[i] = s[i];
    i++;
  }
  return ((char *)dst);
}
