
/*
 * Validates the charset.
 */
int check_charset(char *str, char *charset, int i) {
  int j;

  j = 0;
  while (charset[j]) {
    if (charset[j] != str[i + 1])
      return (0);
    i++;
    j++;
  }
  return (1);
}
