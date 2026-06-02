
#include "hotrace.h"

void ft_putendl_fd(const char *s, int fd) {
  write(fd, s, ft_strlen(s) * sizeof(char));
  write(fd, "\n", sizeof(char));
}

void ft_putstr_fd(char *s, int fd) {
  if (s == NULL)
    return;
  write(fd, s, ft_strlen(s));
}
