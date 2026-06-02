
/*
 * Copies at most `n` characters from a string into another string.
 * Strings must be initialized and big enough.
 *
 * @see	strnew
 * @see	strcpy
 *
 * @param	dest	string to copy to
 * @param	src		string to copy
 * @param	n		max number of characters to copy
 *
 * @returns	dest
 */
char *ft_strncpy(char *dest, char *src, unsigned int n) {
  unsigned int i;

  i = 0;
  while (i < n && src[i] != '\0') {
    dest[i] = src[i];
    i++;
  }
  while (i < n) {
    dest[i] = '\0';
    i++;
  }
  return (dest);
}
