
#include "cub3d.h"

bool is_valid_position(t_data *data, double x, double y) {
  int map_x;
  int map_y;

  map_x = (int)x;
  map_y = (int)y;
  if (map_x < 0 || map_y < 0 || !data->map[map_y] || !data->map[map_y][map_x])
    return (false);
  return (true);
}
