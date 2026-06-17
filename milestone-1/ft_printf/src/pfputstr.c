#include "ft_printf.h"
#include "libft.h"
#include <unistd.h>

ssize_t pfputstr(int fd, const char *str) {
  if (!str)
    return (write(fd, "(null)", 6));
  return (write(fd, str, (size_t)ft_strlen(str)));
}
