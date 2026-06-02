
#include "h_main.h"

/*
 * Duplicates a string.
 *
 * @param	src	string to duplicate
 *
 * @returns	string if everything worked
 * @returns	NULL if malloc failed
 */
char *ft_strdup(char *src) {
  int i;
  char *dest;

  dest = malloc(sizeof(char) * (ft_strlen(src) + 1));
  if (dest == 0)
    return (0);
  i = 0;
  while (src[i] != '\0') {
    dest[i] = src[i];
    i++;
  }
  dest[i] = '\0';
  return (dest);
}
