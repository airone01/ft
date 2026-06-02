
#include <unistd.h>

void ft_putstr(char *str) {
  if (*str == '\0')
    return;
  write(1, str, 1);
  ft_putstr(str + sizeof(char));
}

// int	main(void)
// {
// 	ft_putstr ("Far out in the uncharted backwaters...");
// }
