
#include "libft.h"

char *ft_substr(char const *s, unsigned int start, size_t len) {
  char *dst;

  if (start >= ft_strlen(s))
    return (ft_strdup(""));
  s = &(s[start]);
  if (len > ft_strlen(s))
    len = ft_strlen(s);
  dst = ft_calloc(len + 1, sizeof(char));
  if (!dst)
    return (0);
  ft_strlcpy(dst, s, len + 1);
  return (dst);
}
