
#include "pipex.h"

/**
 * Splits the command into the arguments and finds the binary.
 * Then, it places the binary in the first argument.
 *
 * @param cmd	The command
 *
 * @returns		The command as an array of strings
 *
 * @exception	ENOMEM if malloc fails
 */
char **cmda_args(t_ctx *app, char *cmd) {
  char **args;
  char *bin_og;
  char *bin;

  args = ft_split(cmd, ' ');
  if (!args)
    app_exit_errno(*app, ENOMEM);
  bin_og = args[0];
  bin = find_bin(app, bin_og);
  free(bin_og);
  args[0] = NULL;
  if (!bin) {
    free_strings(args);
    app_exit_errno(*app, ENOENT);
  }
  args[0] = bin;
  return (args);
}
