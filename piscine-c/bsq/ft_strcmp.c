
/*
 * Compares two strings.
 * Mainly used to tell if the strings are equal.
 *
 * @param	s1	first string to ccompare
 * @param	s2	second string to compare
 *
 * @returns	0 if strings are equal
 * @returns	negative int if s1 < s2
 * @returns	positive int if s1 > s2
 */
int ft_strcmp(char *s1, char *s2) {
  int i;

  i = 0;
  while (s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i])
    i++;
  if (s1[i] == '\0' && s2[i] == '\0')
    return (0);
  else
    return (s1[i] - s2[i]);
}
