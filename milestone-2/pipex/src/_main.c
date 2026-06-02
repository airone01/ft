
#include "pipex.h"

/**
 * @brief	Entry point of the program
 */
int main(int argc, char **argv, char **envp) {
  t_ctx app;

  app = app_new(envp);
  args_valid(&app, argc, argv);
  populate_cmdas(&app, argc, argv);
  exec_cmdas(app);
  app_free(app);
  return (0);
}
