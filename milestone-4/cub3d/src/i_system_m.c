#include "cub3d.h"
#include <unistd.h>

void free_door_system(t_data *data) { (void)data; }

void init_door_system(t_data *data) { (void)data; }

void update_door_animations(t_data *data) { (void)data; }

t_door *get_door_at(t_data *data, int x, int y) {
  (void)data;
  (void)x;
  (void)y;
  return (NULL);
}

void toggle_door(t_data *data, int x, int y) {
  (void)data;
  (void)x;
  (void)y;
}

/*
** We just return false here to avoid soft-locking players.
*/
bool is_door_passable(t_data *data, int x, int y) {
  (void)data;
  (void)x;
  (void)y;
  return (false);
}