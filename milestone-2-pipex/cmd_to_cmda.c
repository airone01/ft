/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_to_cmda.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 18:52:18 by elagouch          #+#    #+#             */
/*   Updated: 2025/01/29 16:54:30 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/**
 * Splits the command into the arguments and finds the binary.
 * Then, it places the binary in the first argument.
 *
 * @param envp	The environment variables
 * @param cmd	The command
 *
 * @returns		The command as an array of strings
 *
 * @exception	ENOMEM if malloc fails
 */
char	**split_args_and_find_bin(t_app *app, char **envp, char *cmd)
{
	char	**cmdas;
	char	*bin_og;
	char	*bin;

	cmdas = ft_split(cmd, ' ');
	if (!cmdas)
		app_exit_errno(*app, ENOMEM);
	bin_og = cmdas[0];
	bin = find_bin(app, envp, bin_og);
	if (!bin)
	{
		free_strings(cmdas);
		app_exit_errno(*app, ENOENT);
	}
	free(bin_og);
	cmdas[0] = bin;
	return (cmdas);
}

/**
 * Converts a list of commands to a list of advanced commands
 *
 * @param cmds	The list of commands
 * @param envp	The environment variables
 *
 * @returns		Itself, transformed as a list of advanced commands
 *
 * @exception	ENOMEM if malloc fails
 */
void	cmds_to_cmdas(t_app *app, char **envp)
{
	t_list	*cmds;
	void	*tmp;

	cmds = app->cmds;
	while (cmds)
	{
		cmds->content = split_args_and_find_bin(app, envp, cmds->content);
		if (!cmds->content)
			app_exit_errno(*app, ENOMEM);
		cmds = cmds->next;
	}
}
