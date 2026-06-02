
#include "minishell.h"

/**
 * @brief Safely frees a string and sets pointer to NULL
 *
 * Prevents double free issues by checking if pointer is NULL first.
 *
 * @param str Pointer to string pointer to free
 */
void safe_free_str(char **str) {
  if (str && *str) {
    free(*str);
    *str = NULL;
  }
}
