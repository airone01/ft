/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_to_cmda.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 18:52:18 by elagouch          #+#    #+#             */
/*   Updated: 2025/01/29 19:31:34 by elagouch         ###   ########.fr       */
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
	char	**args;
	char	*bin_og;
	char	*bin;

	args = ft_split(cmd, ' ');
	if (!args)
		app_exit_errno(*app, ENOMEM);
	bin_og = args[0];
	bin = find_bin(app, envp, bin_og);
	free(bin_og);
	args[0] = NULL;
	if (!bin)
	{
		free_strings(args);
		app_exit_errno(*app, ENOENT);
	}
	args[0] = bin;
	return (args);
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
	t_list	*tmp;
	char	**args;

	cmds = app->cmds;
	while (cmds)
	{
		args = split_args_and_find_bin(app, envp, cmds->content);
		tmp = ft_lstnew(args);
		if (!tmp)
		{
			free_strings(args);
			app_exit_errno(*app, ENOMEM);
		}
		if (app->cmdas)
			ft_lstadd_back(&app->cmdas, tmp);
		else
			app->cmdas = tmp;
		cmds = cmds->next;
	}
}
