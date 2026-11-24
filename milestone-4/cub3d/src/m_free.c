#include "mem.h"
#include "mlx.h"
#include "sprite_bonus.h"
#include <stdlib.h>

static void free_textures(t_data *data) {
  if (data->textures.north.img)
    mlx_destroy_image(data->mlx, data->textures.north.img);
  if (data->textures.south.img)
    mlx_destroy_image(data->mlx, data->textures.south.img);
  if (data->textures.east.img)
    mlx_destroy_image(data->mlx, data->textures.east.img);
  if (data->textures.west.img)
    mlx_destroy_image(data->mlx, data->textures.west.img);
  if (data->textures.door.img)
    mlx_destroy_image(data->mlx, data->textures.door.img);
}

static void free_paths(t_data *data) {
  if (data->texture_n)
    free(data->texture_n);
  if (data->texture_s)
    free(data->texture_s);
  if (data->texture_e)
    free(data->texture_e);
  if (data->texture_w)
    free(data->texture_w);
  if (data->texture_door)
    free(data->texture_door);
  if (data->map_file_path)
    free(data->map_file_path);
  if (data->texture_sprite)
    free(data->texture_sprite);
}

void *free_resources(t_data **data) {
  t_data *d;

  if (!data || !*data)
    return (NULL);
  d = *data;
  free_paths(d);
  free_textures(d);
  free_door_system(d);
  free_sprite_system(d);
  if (d->z_buffer)
    free(d->z_buffer);
  free(d);
  *data = NULL;
  return (NULL);
}