
#include "pipex.h"

/**
 * Frees an advanced command as a list of strings
 *
 * @param cmda	The advanced command
 */
void cmda_free(void *cmda) {
  char **args;

  args = (char **)cmda;
  while (*args) {
    free(*args);
    args++;
  }
  free(cmda);
}
