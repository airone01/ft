
#include "cub3d.h"
#include "ft_printf.h"

bool check_bonus_textures(t_data *data) {
  if (!data->texture_door) {
    ft_printf(RED "Error\nMissing door texture (D)\n" RESET);
    return (true);
  }
  if (!data->texture_sprite) {
    ft_printf(RED "Error\nMissing sprite texture (P)\n" RESET);
    return (true);
  }
  return (false);
}
