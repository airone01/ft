
#include "fdf.h"

void print_memory_error(t_error err) {
  if (err == ERR_MALLOC || err == ERR_MALLOC_MAP || err == ERR_MALLOC_LINE)
    ft_printf("Memory allocation failed\n");
}
