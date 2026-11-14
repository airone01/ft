#include "libft.h"
#include <unistd.h>

ssize_t ft_putchar(char c) { return ft_putchar_fd(c, STDOUT_FILENO); }
