#include "libft.h"
#include <sys/types.h>
#include <unistd.h>

ssize_t ft_putendl_fd(const char *s, int fd) {
  ssize_t r = write(fd, s, ft_strlen(s) * sizeof(char));
  r += write(fd, "\n", sizeof(char));
  return r;
}
