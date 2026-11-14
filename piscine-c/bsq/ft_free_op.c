#include "h_bsq.h"
#include "h_file.h"
#include <stdlib.h>

/*
 * Frees a pointer and returns NULL.
 *
 * @param	ptr1	pointer to free
 * @param	ptr2	pointer to free
 *
 * @returns	NULL
 */
void *free_and_null_map(void *ptr, t_tile **map, t_coords coords) {
  free(ptr);
  bsq_map_free(map, coords);
  return (NULL);
}

/*
 * Frees an array of strings.
 *
 * @param	strs	array of strings
 */
void free_strs(char **strs) {
  while (*strs != NULL) {
    free(*strs);
    strs++;
  }
}
