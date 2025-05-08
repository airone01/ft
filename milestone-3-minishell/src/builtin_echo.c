/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 09:54:10 by elagouch          #+#    #+#             */
/*   Updated: 2025/05/06 15:00:13 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Checks if an argument is the -n option for echo
 *
 * @param arg Argument to check
 * @return bool true if it's the -n option, false otherwise
 */
static bool	is_n_option(char *arg)
{
	int	i;

	if (!arg || ft_strncmp(arg, "-n", 2) != 0)
		return (false);
	i = 2;
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (false);
		i++;
	}
	return (true);
}

/**
 * @brief Executes the echo built-in command
 *
 * @param ctx Context for shell environment
 * @param cmd Command containing arguments
 * @return int Exit status (always 0 for echo)
 */
int	builtin_echo(t_ctx *ctx, t_command *cmd)
{
	int		i;
	bool	new_line;

	(void)ctx;
	new_line = true;
	i = 1;
	while (i <= cmd->arg_count && is_n_option(cmd->args[i]))
	{
		new_line = false;
		i++;
	}
	while (i <= cmd->arg_count)
	{
		ft_printf(cmd->args[i], STDOUT_FILENO);
		if (i < cmd->arg_count)
			ft_putchar_fd(' ', STDOUT_FILENO);
		i++;
	}
	if (new_line)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (0);
}
