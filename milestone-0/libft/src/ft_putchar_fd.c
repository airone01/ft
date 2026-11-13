#include "libft.h"
#include <sys/types.h>
#include <unistd.h>

ssize_t ft_putchar_fd(char c, int fd) { return write(fd, &c, sizeof(char)); }
