
#include "fdf.h"

void print_map_error(t_error err) {
  if (err == ERR_MAP_INVALID_CHAR)
    ft_printf("Invalid character in map\n");
  else if (err == ERR_MAP_IRREGULAR)
    ft_printf("Map must be rectangular\n");
  else if (err == ERR_MAP_TOO_LARGE)
    ft_printf("Map is too large\n");
  else if (err == ERR_MAP_EMPTY_LINE)
    ft_printf("Empty line in map\n");
  else if (err == ERR_MAP_INVALID_COLOR)
    ft_printf("Invalid color format\n");
}
