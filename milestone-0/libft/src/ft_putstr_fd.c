#include "libft.h"
#include <unistd.h>

ssize_t ft_putstr_fd(char *s, int fd) {
  return write(fd, s, ft_strlen(s) * sizeof(char));
}
