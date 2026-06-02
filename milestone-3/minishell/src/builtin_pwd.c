
#include "error.h"

/**
 * @brief Executes the pwd built-in command
 *
 * @return int Exit status (0 for success, non-zero for error)
 */
int builtin_pwd(void) {
  char *pwd;

  pwd = getcwd(NULL, 0);
  if (!pwd)
    return (error(NULL, "pwd", ERR_NO_PWD));
  ft_printf("%s\n", pwd);
  free(pwd);
  return (0);
}
