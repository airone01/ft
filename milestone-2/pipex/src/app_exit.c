
#include "pipex.h"

/**
 * @brief	Exits the program safely with an error number
 */
void app_exit_errno(t_ctx app, unsigned long errno_p) {
  errno = (int)errno_p;
  app_exit(app);
}

/**
 * @brief	Exits the program safely
 */
void app_exit(t_ctx app) {
  app_free(app);
  perror("Error");
  exit(errno);
}
