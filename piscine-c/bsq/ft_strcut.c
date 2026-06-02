
#include "h_main.h"

/*
 * Allocates and cuts a word from `start` to `finish`.
 *
 * @param	str		source string
 * @param	start	starting index
 * @param	finish	ending index
 *
 * @returns duplicated and cut string
 */
char *ft_strcut(char *str, int start, int finish) {
  char *word;
  int i;

  i = 0;
  word = (char *)malloc((finish - start + 1) * sizeof(char));
  while (start < finish)
    word[i++] = str[start++];
  word[i] = '\0';
  return (word);
}
