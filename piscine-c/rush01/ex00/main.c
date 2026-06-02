
#include "rush.h"
#include <stdlib.h>

int main(int argc, char **argv) {
  unsigned int **grid;
  unsigned int magic;
  unsigned int size;
  unsigned int i;

  if (argc != 2) {
    ft_putstr("Error\n");
    return (1);
  }
  size = read_grid_axis_size(argv[1]) + 2;
  magic = ft_facto(size - 2);
  grid = make_grid(size);
  if (!grid) {
    ft_putstr("Error\n");
    return (1);
  }
  read_grid(argv[1], grid, size);
  if (solve_max(grid, size) || solve_min(grid, size) ||
      !brute_try(grid, size, magic)) {
    ft_putstr("Error\n");
    i = 0;
    while (i < size)
      free(grid[i++]);
    free(grid);
    return (1);
  }
  i = 0;
  while (i < size)
    free(grid[i++]);
  free(grid);
  return (0);
}
