
#include "fdf.h"

void print_mlx_error(t_error err) {
  if (err == ERR_MLX_INIT)
    ft_printf("Failed to initialize MLX\n");
  else if (err == ERR_MLX_WINDOW)
    ft_printf("Failed to create window\n");
  else if (err == ERR_MLX_IMAGE)
    ft_printf("Failed to create image\n");
}
