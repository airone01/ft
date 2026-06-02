
#include "fdf.h"

void print_arg_error(t_error err) {
  if (err == ERR_ARG_COUNT)
    ft_printf("Usage: ./fdf <filename>\n");
  else if (err == ERR_ARG_INVALID_FILE)
    ft_printf("Invalid file provided\n");
}
