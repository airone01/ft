
// #include <stdio.h>

int ft_strlen(char *str) {
  if (*str == '\0')
    return (0);
  return (ft_strlen(str + sizeof(char)) + 1);
}

// int	main(int argc, char **argv)
// {
// 	(void) argc;
// 	printf("%d", ft_strlen(argv[1]));
// }
