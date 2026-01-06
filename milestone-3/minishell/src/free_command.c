/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 16:44:34 by elagouch          #+#    #+#             */
/*   Updated: 2025/05/06 14:38:27 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Frees a redirection structure
 *
 * Frees memory and closes open file descriptors
 *
 * @param redir Redirection to free
 */
static void	free_redirection(t_redir *redir)
{
	if (!redir)
		return ;
	if (redir->filename)
		free(redir->filename);
	if (redir->fd != -1)
		close(redir->fd);
	free(redir);
}

/**
 * @brief Frees all redirections in a list
 *
 * @param redir First redirection in the list
 */
static void	free_all_redirections(t_redir *redir)
{
	t_redir	*current;
	t_redir	*next;

	current = redir;
	while (current)
	{
		next = current->next;
		free_redirection(current);
		current = next;
	}
}

/**
 * @brief Frees a command structure
 *
 * Frees arguments, redirections, and command structure
 *
 * @param cmd Command to free
 */
void	free_command(t_command *cmd)
{
	int	i;

	if (!cmd)
		return ;
	if (cmd->args)
	{
		i = 0;
		while (i <= cmd->arg_count)
		{
			if (cmd->args[i])
				free(cmd->args[i]);
			i++;
		}
		free(cmd->args);
	}
	if (cmd->redirection)
		free_all_redirections(cmd->redirection);
	free(cmd);
}

/**
 * @brief Frees all commands in a list
 *
 * @param cmd First command in the list
 */
void	free_all_commands(t_command *cmd)
{
	t_command	*current;
	t_command	*next;

	current = cmd;
	while (current)
	{
		next = current->next;
		free_command(current);
		current = next;
	}
}
