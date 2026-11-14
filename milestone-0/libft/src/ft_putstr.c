#include "libft.h"
#include <sys/types.h>
#include <unistd.h>

ssize_t ft_putstr(char *s) { return ft_putstr_fd(s, STDOUT_FILENO); }
