/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 16:45:10 by elagouch          #+#    #+#             */
/*   Updated: 2025/05/06 15:23:29 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "execute.h" // for apply_*_redirection

/**
 * @brief Applies all redirections for a command
 *
 * @param cmd Command structure
 * @return bool true on success, false on error
 */
bool	apply_redirections(t_command *cmd)
{
	if (!cmd || !cmd->redirection)
		return (true);
	if (!apply_input_redirection(cmd))
		return (false);
	if (!apply_output_redirection(cmd))
		return (false);
	return (true);
}

/**
 * @brief Saves original standard file descriptors
 *
 * @param stdin_fd Pointer to store original stdin fd
 * @param stdout_fd Pointer to store original stdout fd
 * @return bool true on success, false on error
 */
bool	save_original_fds(int *stdin_fd, int *stdout_fd)
{
	*stdin_fd = dup(STDIN_FILENO);
	if (*stdin_fd == -1)
		return (error("dup", "redirection", ERR_FD), false);
	*stdout_fd = dup(STDOUT_FILENO);
	if (*stdout_fd == -1)
	{
		close(*stdin_fd);
		return (error("dup", "redirection", ERR_FD), false);
	}
	return (true);
}

/**
 * @brief Restores original standard file descriptors
 *
 * @param stdin_fd Original stdin fd
 * @param stdout_fd Original stdout fd
 */
void	restore_original_fds(int stdin_fd, int stdout_fd)
{
	if (stdin_fd != -1)
	{
		dup2(stdin_fd, STDIN_FILENO);
		close(stdin_fd);
	}
	if (stdout_fd != -1)
	{
		dup2(stdout_fd, STDOUT_FILENO);
		close(stdout_fd);
	}
}
