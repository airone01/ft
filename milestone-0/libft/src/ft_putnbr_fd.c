
#include "libft.h"

void ft_putnbr_fd(int n, int fd) {
  if (n == -2147483648) {
    write(fd, "-2147483648", 11 * sizeof(char));
    return;
  }
  if (n < 0) {
    ft_putchar_fd('-', fd);
    ft_putnbr_fd(-n, fd);
    return;
  }
  if (n > 9) {
    ft_putnbr_fd(n / 10, fd);
    ft_putchar_fd((char)(n % 10) + '0', fd);
    return;
  }
  ft_putchar_fd((char)n + '0', fd);
}
