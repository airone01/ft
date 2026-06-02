
#include "libft.h"

char *ft_strmapi(char const *s, char (*f)(size_t, char)) {
  size_t len;
  size_t i;
  char *dst;

  len = ft_strlen(s);
  dst = ft_calloc(len + 1, sizeof(char));
  if (!dst)
    return (0);
  i = 0;
  while (s[i]) {
    dst[i] = f(i, s[i]);
    i++;
  }
  return (dst);
}
