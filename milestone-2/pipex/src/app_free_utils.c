
#include "pipex.h"

/**
 * @brief	Does absolutely nothing
 */
void nothing(void *ptr) { (void)ptr; }

/**
 * @brief	Frees an array of strings
 */
void free_strings(char **strings) {
  char **tmp;

  tmp = strings;
  while (tmp && *tmp) {
    free(*tmp);
    tmp++;
  }
  free(strings);
}
