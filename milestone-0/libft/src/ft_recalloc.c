
#include "libft.h"

void *ft_recalloc(void *ptr, size_t old_size, size_t new_size) {
  void *new_ptr;

  if (old_size >= new_size)
    return (ptr);
  new_ptr = ft_calloc(1, new_size);
  if (!new_ptr)
    return (NULL);
  if (ptr) {
    ft_memcpy(new_ptr, ptr, old_size);
    free(ptr);
  }
  return (new_ptr);
}
