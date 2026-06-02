
#include <unistd.h>

void ft_putstr(char *str) {
  if (*str == '\0')
    return;
  write(1, str, 1);
  ft_putstr(str + sizeof(char));
}

// int	main(int argc, char **argv)
// {
// 	(void) argc;
// 	ft_putstr(argv[1]);
// }
