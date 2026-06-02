
// #include <stdio.h>

char *ft_strlowcase(char *str) {
  int i;
  const char offset = 'a' - 'A';

  i = 0;
  while (str[i] != '\0') {
    if (str[i] >= 'A' && str[i] <= 'Z') {
      str[i] += offset;
    }
    i++;
  }
  return (str);
}

// int	main(void)
// {
// 	char	entry[] = "HELLO, WORLD!";
// 	printf("here: %s\n", ft_strlowcase(entry));
// }
