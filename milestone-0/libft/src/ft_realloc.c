
#include "libft.h"

void *ft_realloc(void *ptr, size_t old_size, size_t new_size) {
  void *new_ptr;

  if (new_size == 0) {
    free(ptr);
    return (NULL);
  }
  new_ptr = malloc(new_size);
  if (!new_ptr) {
    free(ptr);
    return (NULL);
  }
  if (ptr) {
    ft_memcpy(new_ptr, ptr, (size_t)ft_min((long)old_size, (long)new_size));
    free(ptr);
  }
  return (new_ptr);
}
