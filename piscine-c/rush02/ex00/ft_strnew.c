
#include <stdlib.h>

/*
 * Allocates a new string array and initializes it.
 */
char *ft_strnew(int size) {
  int i;
  char *dest;

  dest = malloc(size * sizeof(char));
  if (dest != NULL) {
    i = 0;
    while (i < size) {
      dest[i] = '\0';
      i++;
    }
  }
  return (dest);
}
