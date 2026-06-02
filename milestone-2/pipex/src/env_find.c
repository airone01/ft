
#include "pipex.h"

/**
 * Search for a variable in the environment
 *
 * @param app		The app structure
 * @param var		The variable to search for
 *
 * Warning: The searched variable *must* end with a '='
 *
 * If the variable is not found, return NULL and don't error out.
 */
char *env_find(t_ctx app, char *var) {
  size_t i;
  size_t len;
  char *path;

  i = 0;
  len = ft_strlen(var);
  while (app.envp[i]) {
    if (ft_strncmp(app.envp[i], var, len) == 0) {
      path = ft_strdup(app.envp[i] + 5);
      return (path);
    }
    i++;
  }
  return (NULL);
}
