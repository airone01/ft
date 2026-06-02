
#include "cub3d.h"
#include "libft.h"
#include "texture.h"
#include <stdbool.h>

bool parse_texture_no_so(t_data *data, char *path, const char *cardinal) {
  if (ft_strcmp(cardinal, "NO ") == 0) {
    if (check_text_duplicate(data, cardinal, data->texture_n))
      return (true);
    data->texture_n = ft_strtrim(path, "\n");
    return (true);
  }
  if (ft_strcmp(cardinal, "SO ") == 0) {
    if (check_text_duplicate(data, cardinal, data->texture_s))
      return (true);
    data->texture_s = ft_strtrim(path, "\n");
    return (true);
  }
  return (false);
}

bool parse_texture_we_ea(t_data *data, char *path, const char *cardinal) {
  if (ft_strcmp(cardinal, "WE ") == 0) {
    if (check_text_duplicate(data, cardinal, data->texture_w))
      return (true);
    data->texture_w = ft_strtrim(path, "\n");
    return (true);
  }
  if (ft_strcmp(cardinal, "EA ") == 0) {
    if (check_text_duplicate(data, cardinal, data->texture_e))
      return (true);
    data->texture_e = ft_strtrim(path, "\n");
    return (true);
  }
  return (false);
}
