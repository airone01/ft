
#include "libft.h"

char *ft_strrchr(const char *s, char c) {
  char *se;

  if (!s)
    return (NULL);
  se = NULL;
  while (*s) {
    if (*s == (char)c)
      se = (char *)s;
    s++;
  }
  if (*s == (char)c)
    se = (char *)s;
  return (se);
}
