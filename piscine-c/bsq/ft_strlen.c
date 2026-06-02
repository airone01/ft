
#include "h_main.h"

/*
 * Gets the length of a string.
 *
 * @param	str	string to get length from
 *
 * @retuns	length of str
 */
int ft_strlen(char *str) {
  int i;

  i = 0;
  while (str[i] != '\0')
    i++;
  return (i);
}
