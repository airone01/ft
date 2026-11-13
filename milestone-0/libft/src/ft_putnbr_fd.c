#include "libft.h"
#include <sys/types.h>
#include <unistd.h>

ssize_t ft_putnbr_fd(int n, int fd) {
  ssize_t r = 0;
  if (n == -2147483648 /* TODO: magic */) {
    r += write(fd, "-2147483648", 11 * sizeof(char));
    return r;
  }
  if (n < 0) {
    r += ft_putchar_fd('-', fd);
    r += ft_putnbr_fd(-n, fd);
    return r;
  }
  if (n > 9) {
    r += ft_putnbr_fd(n / 10, fd);
    r += ft_putchar_fd((char)(n % 10) + '0', fd);
    return r;
  }
  r += ft_putchar_fd((char)n + '0', fd);
  return r;
}
