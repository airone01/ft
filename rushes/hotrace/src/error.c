
#include "hotrace.h"

/**
 * @brief	Displays an error message.
 *
 * @param	msg	The error message.
 * @param	err	The error code.
 */
void error(char *msg, int err) {
  (void)err;
  if (msg)
    ft_putendl_fd(msg, 2);
}
