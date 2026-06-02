
#include "libft.h"

char *ft_strchr(const char *s, char c) {
  while (*s != (char)c)
    if (!*s++)
      return (NULL);
  return ((char *)s);
}
