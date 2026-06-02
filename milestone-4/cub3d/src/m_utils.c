
#include "libft.h"
#include "mem.h"

bool init_map_buffer(t_map_buffer *buffer) {
  buffer->capacity = 50;
  buffer->count = 0;
  buffer->max_width = 0;
  buffer->lines = ft_calloc((unsigned long)buffer->capacity, sizeof(char *));
  return (buffer->lines == NULL);
}
