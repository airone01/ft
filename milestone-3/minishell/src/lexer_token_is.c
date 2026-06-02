
#include "minishell.h"

/**
 * @brief Checks if a token is a redirection token
 *
 * @param tok Token type to check
 * @return bool true if token is a redirection, false otherwise
 */
bool token_is_redirection(t_token_type type) {
  return (type == TOK_REDIR_FROM || type == TOK_REDIR_TO ||
          type == TOK_HERE_DOC_FROM || type == TOK_HERE_DOC_TO);
}
