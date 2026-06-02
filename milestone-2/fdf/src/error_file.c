
#include "fdf.h"

void print_file_error(t_error err) {
  if (err == ERR_FILE_OPEN)
    ft_printf("%s\n", strerror(errno));
  else if (err == ERR_FILE_READ)
    ft_printf("Failed to read file\n");
  else if (err == ERR_FILE_EXTENSION)
    ft_printf("File must have .fdf extension\n");
  else if (err == ERR_FILE_EMPTY)
    ft_printf("File is empty\n");
}
