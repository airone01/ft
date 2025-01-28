/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_to_cmda.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 18:52:18 by elagouch          #+#    #+#             */
/*   Updated: 2025/01/28 20:00:46 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/**
 * Splits the command into the binary and the arguments and populates a t_cmda
 *
 * @param envp	The environment variables
 * @param cmd	The command
 *
 * @returns		The advanced command
 *
 * @exception	ENOMEM if malloc fails
 */
t_cmda	*split_args_and_find_bin(char **envp, char *cmd)
{
	char	**args;
	t_cmda	*cmda;

	cmda = ft_calloc(1, sizeof(t_cmda));
	cmda->args = ft_split(cmd, ' ');
	if (!cmda->args)
		perror_errno_and_exit(ENOMEM);
	cmda->bin = find_bin(envp, cmda->args[0]);
	if (!cmda->bin)
		perror_errno_and_exit(ENOENT);
	return (cmda);
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
t_list	*cmds_to_cmdas(t_list *cmds, char **envp)
{
	t_cmda	*cmda;
	t_list	*cmds_og;
	char	**args;

	cmds_og = cmds;
	while (cmds)
	{
		cmda = split_args_and_find_bin(envp, cmds->content);
		cmds->content = cmda;
		cmds = cmds->next;
	}
	return (cmds_og);
}
