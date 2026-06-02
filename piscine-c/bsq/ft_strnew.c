
#include <stdlib.h>

/*
 * Allocates a new string array and initializes it.
 *
 * @param	size	number of chars of the new string including the '\0'
 *
 * @returns	allocated string
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
