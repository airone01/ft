
#include "cub3d.h"
#include <unistd.h>

bool load_bonus_textures(t_data *data, char *door_path) {
  (void)data;
  (void)door_path;
  return (false);
}

t_texture *get_wall_texture_bonus(t_data *data, t_textures *textures,
                                  t_ray *ray) {
  (void)ray;
  (void)data;
  (void)textures;
  return (NULL);
}
