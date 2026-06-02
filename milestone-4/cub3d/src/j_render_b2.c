
#include "cub3d.h"

static void calculate_sprite_distances(t_data *data) {
  int i;
  double dx;
  double dy;

  i = -1;
  while (++i < data->sprite_sys.count) {
    if (data->sprite_sys.sprites[i].active) {
      dx = data->player.pos_x - data->sprite_sys.sprites[i].x;
      dy = data->player.pos_y - data->sprite_sys.sprites[i].y;
      data->sprite_sys.sprites[i].distance = dx * dx + dy * dy;
    }
  }
}

void sort_sprites_by_distance(t_data *data) {
  int i;
  int j;
  int temp;

  calculate_sprite_distances(data);
  i = -1;
  while (++i < data->sprite_sys.count)
    data->sprite_sys.render_order[i] = i;
  i = -1;
  while (++i < data->sprite_sys.count - 1) {
    j = i;
    while (++j < data->sprite_sys.count) {
      if (data->sprite_sys.sprites[data->sprite_sys.render_order[i]].distance <
          data->sprite_sys.sprites[data->sprite_sys.render_order[j]].distance) {
        temp = data->sprite_sys.render_order[i];
        data->sprite_sys.render_order[i] = data->sprite_sys.render_order[j];
        data->sprite_sys.render_order[j] = temp;
      }
    }
  }
}
