#ifndef SYS_MAP_H
#define SYS_MAP_H

#include <stdint.h>

#define SYS_MAP "CUB_MAP"

typedef struct {
  uint8_t **map;
} map_data;

int sys_map_init(void);

void sys_map_free(void);

#endif /* SYS_MAP_H */