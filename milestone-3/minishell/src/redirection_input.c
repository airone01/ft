/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_input.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 15:18:51 by elagouch          #+#    #+#             */
/*   Updated: 2025/05/06 15:22:53 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"

/**
 * @brief Opens and validates a file for input redirection
 *
 * @param redir Redirection structure
 * @param is_heredoc Boolean flag indicating if redirection is a heredoc
 * @return int File descriptor or -1 on error
 */
static int	open_input_file(t_redir *redir, bool is_heredoc)
{
	int	fd;

	if (is_heredoc)
		fd = redir->fd;
	else
		fd = open(redir->filename, O_RDONLY);
	if (!is_heredoc && fd == -1)
	{
		error(redir->filename, "redirection", ERR_NO_FILE);
		return (-1);
	}
	return (fd);
}

/**
 * @brief Redirects the input file descriptor to stdin
 *
 * @param fd File descriptor to redirect
 * @return bool true on success, false on error
 */
static bool	redirect_to_stdin(int fd)
{
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		close(fd);
		error("dup2", "redirection", ERR_FD);
		return (false);
	}
	close(fd);
	return (true);
}

/**
 * @brief Applies input redirection for a command
 *
 * @param cmd Command structure
 * @return bool true on success, false on error
 */
bool	apply_input_redirection(t_command *cmd)
{
	t_redir	*redir;
	int		fd;
	bool	is_heredoc;

	redir = cmd->redirection;
	while (redir)
	{
		if (redir->type == TOK_REDIR_FROM || redir->type == TOK_HERE_DOC_FROM)
		{
			is_heredoc = (redir->type == TOK_HERE_DOC_FROM);
			fd = open_input_file(redir, is_heredoc);
			if (fd == -1)
				return (false);
			if (!redirect_to_stdin(fd))
				return (false);
			if (is_heredoc)
				redir->fd = -1;
		}
		redir = redir->next;
	}
	return (true);
}
