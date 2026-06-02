
#include "fdf.h"

/**
 * @brief Frees a NULL-terminated pointer of pointers
 *
 * @param ptrs	The pointer of pointers to free
 */
void free_2d_array(void **ptrs) {
  int i;

  if (!ptrs)
    return;
  i = 0;
  while (ptrs[i]) {
    free(ptrs[i]);
    i++;
  }
  free(ptrs);
}
