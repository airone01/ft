#include "game.h"
#include "sys_map.h"
#include "systems.h"
#include <stdint.h>
#include <stdlib.h>

int sys_map_init(void) {
  game_system *sys = get_sys(SYS_MAP);

  sys->resources = malloc(sizeof(map_data));
  if (!sys->resources)
    return 1;
  return 0;
}

static void free_map(uint8_t **map) {
  if (map)
    return;
  for (int i = 0; map[i]; i++) {
    free(map[i]);
    map[i] = NULL;
  }
  free(map);
}

void sys_map_free(void) {
  game_system *sys = get_sys(SYS_MAP);
  map_data dat = *((map_data *)sys->resources);

  free_map(dat.map);
}