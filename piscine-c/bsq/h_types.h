
#ifndef H_TYPES_H
#define H_TYPES_H

typedef struct s_coords {
  int x;
  int y;
} t_coords;
typedef enum s_tile {
  epty = 0,
  obst = 1,
  full = 9,
} t_tile;
typedef struct s_tiles {
  char epty;
  char obst;
  char full;
} t_tiles;
typedef struct s_map {
  t_coords coords;
  t_tiles tiles;
  t_tile **map;
} t_map;
typedef enum e_bool { false, true } bool;
typedef struct s_strsplit_args {
  unsigned long *i;
  unsigned long *j;
  char **split;
  char *str;
  char *c;
  int *index;
} t_strsplit_args;

#endif
