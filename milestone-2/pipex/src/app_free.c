
#include "pipex.h"

/**
 * @brief	Frees the whole app structure
 */
void app_free(t_ctx app) {
  if (app.bonus_pipes[0] != -1)
    close(app.bonus_pipes[0]);
  if (app.bonus_pipes[1] != -1)
    close(app.bonus_pipes[1]);
  ft_lstclear(&app.cmdas, (void (*)(void *))free_strings);
}
