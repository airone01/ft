
#include "minishell.h"

/**
 * @brief Adds a redirection to a command
 *
 * @param cmd Command to add redirection to
 * @param type Redirection type (< > << >>)
 * @param filename Target filename
 * @return int 0 on success, -1 on failure
 */
int command_add_redirection(t_command *cmd, t_token_type type, char *filename) {
  t_redir *redir;
  t_redir *current;

  if (!cmd || !filename)
    return (-1);
  redir = malloc(sizeof(t_redir));
  if (!redir)
    return (-1);
  redir->type = type;
  redir->fd = -1;
  redir->filename = ft_strdup(filename);
  if (!redir->filename)
    return (free(redir), -1);
  redir->next = NULL;
  if (!cmd->redirection)
    cmd->redirection = redir;
  else {
    current = cmd->redirection;
    while (current->next)
      current = current->next;
    current->next = redir;
  }
  return (0);
}
