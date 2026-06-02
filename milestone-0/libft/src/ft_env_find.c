
#include "libft.h"

char *ft_env_find(char **envp, const char *var) {
  unsigned long len;
  unsigned long i;
  char *path;

  i = 0;
  len = ft_strlen(var);
  while (envp[i]) {
    if (ft_strncmp(envp[i], var, len) == 0) {
      path = ft_strdup(envp[i] + len);
      return (path);
    }
    i++;
  }
  return (NULL);
}
