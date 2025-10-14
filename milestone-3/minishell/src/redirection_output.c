/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_output.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 15:19:54 by elagouch          #+#    #+#             */
/*   Updated: 2025/05/06 15:22:59 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"

/**
 * @brief Determines flags for output redirection based on type
 *
 * @param redir_type Redirection token type
 * @return int Flags for open() system call
 */
static int	get_output_flags(t_token_type redir_type)
{
	if (redir_type == TOK_REDIR_TO)
		return (O_WRONLY | O_CREAT | O_TRUNC);
	else
		return (O_WRONLY | O_CREAT | O_APPEND);
}

/**
 * @brief Opens an output file with appropriate flags
 *
 * @param filename File to open
 * @param flags Open flags
 * @return int File descriptor or -1 on error
 */
static int	open_output_file(char *filename, int flags)
{
	int	fd;

	fd = open(filename, flags, 0644);
	if (fd == -1)
	{
		error(filename, "redirection", ERR_NO_PERMS);
		return (-1);
	}
	return (fd);
}

/**
 * @brief Applies output redirection for a command
 *
 * @param cmd Command structure
 * @return bool true on success, false on error
 */
bool	apply_output_redirection(t_command *cmd)
{
	t_redir	*redir;
	int		fd;
	int		flags;

	redir = cmd->redirection;
	while (redir)
	{
		if (redir->type == TOK_REDIR_TO || redir->type == TOK_HERE_DOC_TO)
		{
			flags = get_output_flags(redir->type);
			fd = open_output_file(redir->filename, flags);
			if (fd == -1)
				return (false);
			if (dup2(fd, STDOUT_FILENO) == -1)
			{
				close(fd);
				return (error("dup2", "redirection", ERR_FD), false);
			}
			close(fd);
		}
		redir = redir->next;
	}
	return (true);
}
