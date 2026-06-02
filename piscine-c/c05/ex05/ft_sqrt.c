
int ft_sqrt(int nb) {
  int i;

  if (nb < 1)
    return (0);
  i = 1;
  while ((i * i) < nb)
    i++;
  if ((i * i) == nb)
    return (i);
  return (0);
}

// #include <stdio.h>
// #include <stdlib.h>
// #include <math.h>
// int	main(int argc, char **argv)
// {
// 	(void) argc;
// 	printf("%d", ft_sqrt(atoi(argv[1])));
// }
