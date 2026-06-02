
#include "cub3d.h"
#include "door_bonus.h"
#include "fps_extra.h"
#include "minimap_bonus.h"
#include "sprite_bonus.h"

void handle_render_bonus_features(t_data *data) {
  draw_minimap(data);
  update_door_animations(data);
  update_sprite_animations(data);
}

void handle_render_extra_features(t_data *data) {
  update_fps_counter(data);
  display_fps(data);
}
