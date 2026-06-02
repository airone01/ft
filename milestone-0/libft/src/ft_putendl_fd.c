
#include "libft.h"

void ft_putendl_fd(const char *s, int fd) {
  write(fd, s, ft_strlen(s) * sizeof(char));
  write(fd, "\n", sizeof(char));
}
