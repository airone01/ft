#include "libft.h"
#include <unistd.h>

void rush(int x, int y);

// Check if it's a number
int ft_is_numeric(char c) {
  if (c >= '0' && c <= '9')
    return (1);
  return (0);
}

int check_xy(int x, int y, char **argv) {
  if (x == 0 || y == 0) {
    ft_putstr("L'un de vos arguments n'est pas valable.\n");
    return (1);
  }
  if (argv[1][0] == '-' || argv[2][0] == '-') {
    ft_putstr("Le programme ne supporte pas les arguments negatifs.\n");
    return (1);
  }
  if (x > 46340 || y > 46340) {
    ft_putstr("Un de vos arguments est trop grand.\n");
    ft_putstr("Veuillez utiliser des valeurs plus petites.\n");
    return (1);
  }
  return (0);
}

int main(int argc, char **argv) {
  int x;
  int y;

  x = 0;
  y = 0;
  if (argc != 3) {
    ft_putstr_fd("Usage: rush <x> <y>\n", STDERR_FILENO);
    return (1);
  }
  x = ft_atoi(argv[1]);
  y = ft_atoi(argv[2]);
  if (check_xy(x, y, argv))
    return (1);
  rush(x, y);
}
