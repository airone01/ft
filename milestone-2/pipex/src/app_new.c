
#include "pipex.h"

/**
 * @brief	Initializes the app structure
 */
t_ctx app_new(char **envp) {
  t_ctx app;

  app.cmdas = NULL;
  app.fd_file_in = -1;
  app.fd_file_out = -1;
  app.bonus_pipes[0] = -1;
  app.bonus_pipes[1] = -1;
  app.envp = envp;
  return (app);
}
