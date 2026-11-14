#include "libft.h"

char *ft_strcat(char *dest, char *src) {
  int dest_len;
  int src_len;
  int i;

  dest_len = ft_strlen(dest);
  src_len = ft_strlen(src);
  i = 0;
  while (i < src_len) {
    dest[i + dest_len] = src[i];
    i++;
  }
  return (dest);
}
