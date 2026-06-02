
#include "h_main.h"

t_map *all_final(t_tile **map, t_tiles tiles, char **strs, t_coords coords) {
  t_map *final;

  final = malloc(sizeof(t_map));
  free_strs(strs);
  free(strs);
  if (final == NULL) {
    free(map);
    return (free_and_null(strs));
  }
  final->map = map;
  final->tiles = tiles;
  final->coords = coords;
  return (final);
}
