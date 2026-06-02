
int ft_iterative_factorial(int nb) {
  int i;
  int count;

  if (nb < 0)
    return (0);
  i = 1;
  count = 1;
  while (i <= nb) {
    count *= i;
    i++;
  }
  return (count);
}

// #include <stdio.h>
// #include <stdlib.h>
// int	main(int argc, char **argv)
// {
// 	(void) argc;
// 	printf("%d", ft_iterative_factorial(atoi(argv[1])));
// }
