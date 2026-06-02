
#include "libft.h"

size_t ft_strlcat(char *dst, const char *src, size_t size) {
  size_t dst_len;
  size_t src_len;
  size_t i;

  src_len = ft_strlen(src);
  dst_len = ft_strlen(dst);
  if (size <= dst_len)
    return (size + src_len);
  i = 0;
  while (size && src[i] && (dst_len + i) < (size - 1)) {
    dst[dst_len + i] = src[i];
    i++;
  }
  dst[dst_len + i] = '\0';
  return (dst_len + src_len);
}
