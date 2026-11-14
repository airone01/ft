#include "libft.h"
#include <sys/types.h>
#include <unistd.h>

ssize_t ft_putend(const char *s) { return ft_putendl_fd(s, STDOUT_FILENO); }
