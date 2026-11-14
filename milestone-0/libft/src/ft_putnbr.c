#include "libft.h"
#include <unistd.h>

ssize_t ft_putnbr(int n) { return ft_putnbr_fd(n, STDOUT_FILENO); }
