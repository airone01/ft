
#include "libft.h"
#include <stdbool.h>

bool config_line_condition(char *trimmed) {
  return (!ft_strncmp(trimmed, "NO ", 3) || !ft_strncmp(trimmed, "SO ", 3) ||
          !ft_strncmp(trimmed, "WE ", 3) || !ft_strncmp(trimmed, "EA ", 3) ||
          !ft_strncmp(trimmed, "D ", 2) || !ft_strncmp(trimmed, "P ", 2) ||
          !ft_strncmp(trimmed, "F ", 2) || !ft_strncmp(trimmed, "C ", 2));
}
