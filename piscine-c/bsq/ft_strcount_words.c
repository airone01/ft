
/*
 * Counts words in a string, separated by a given separator.
 *
 * @param	str	string to count in
 * @param	sep	char suposedly used as separator
 *
 * @returns	amount of words
 */
int ft_strcount_words_sep(char *str, char sep) {
  int sum;
  int i;

  sum = 0;
  i = 0;
  while (str[i]) {
    if (str[i] > 32 && str[i] < 127) {
      if (str[i + 1] == sep)
        sum++;
      if (str[i + 1] == '\0')
        return (sum + 1);
    }
    i++;
  }
  return (sum);
}

/*
 * Counts words in a string, separated by whitespaces.
 *
 * @param	str	string
 *
 * @returns	amount of words
 */
int ft_strcount_words(char *str) { return (ft_strcount_words_sep(str, ' ')); }
