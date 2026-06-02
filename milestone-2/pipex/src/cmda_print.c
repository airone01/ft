
#include "pipex.h"

/**
 * @brief	Prints an advanced command, as an array of strings where the
 * first element is the binary path
 *
 * @param content	The advanced command
 */
void cmda_print(void *content) {
  char **args;

  args = (char **)content;
  ft_printf("bin: %s\n", *args);
  args++;
  while (*args) {
    ft_printf("arg: %s\n", *args);
    args++;
  }
}
