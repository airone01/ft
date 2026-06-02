
#include "libft.h"

void *ft_calloc(size_t nmemb, size_t size) {
  void *ptr;

  if (size && nmemb > SIZE_MAX / size)
    return (0);
  ptr = malloc(size * nmemb);
  if (!ptr)
    return (0);
  return (ft_memset(ptr, 0, size * nmemb));
}
