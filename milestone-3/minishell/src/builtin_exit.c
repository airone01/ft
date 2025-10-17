/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 09:53:27 by elagouch          #+#    #+#             */
/*   Updated: 2025/05/06 15:00:13 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"

/**
 * @brief Checks if a string is a valid number
 *
 * @param str String to check
 * @return bool true if valid number, false otherwise
 */
static bool	is_valid_number(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (false);
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (!str[i])
		return (false);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (false);
		i++;
	}
	return (true);
}

/**
 * @brief Handles numeric argument validation for exit
 *
 * @param arg Argument to check
 * @param exit_code Pointer to store exit code
 * @return bool true if valid, false if error
 */
static bool	validate_exit_arg(char *arg, int *exit_code)
{
	if (!is_valid_number(arg))
	{
		*exit_code = error(arg, "exit", ERR_NUMERIC);
		return (false);
	}
	*exit_code = ft_atoi(arg);
	return (true);
}

/**
 * @brief Executes the exit built-in command
 *
 * @param ctx Context for shell environment
 * @param cmd Command containing arguments
 * @return int Exit status
 */
int	builtin_exit(t_ctx *ctx, t_command *cmd)
{
	int	exit_code;

	exit_code = ctx->exit_status;
	if (cmd->arg_count == 0 || !cmd->args[1])
	{
		ctx->exit_requested = true;
		return (exit_code);
	}
	if (!validate_exit_arg(cmd->args[1], &exit_code))
	{
		ctx->exit_requested = true;
		return (exit_code);
	}
	if (cmd->arg_count > 1)
		return (error(NULL, "exit", ERR_TOO_MANY_ARGS));
	ctx->exit_status = exit_code;
	ctx->exit_requested = true;
	return (exit_code);
}
