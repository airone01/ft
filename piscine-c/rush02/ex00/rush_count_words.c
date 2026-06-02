
int count_words(char *str) {
  int sum;
  int i;

  sum = 0;
  i = 0;
  while (str[i]) {
    if (str[i] > 32 && str[i] < 127) {
      if (str[i + 1] == ' ')
        sum++;
      if (str[i + 1] == '\0')
        return (sum + 1);
    }
    i++;
  }
  return (sum);
}
