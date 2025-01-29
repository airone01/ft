/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_to_cmda.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 18:52:18 by elagouch          #+#    #+#             */
/*   Updated: 2025/01/29 15:51:03 by elagouch         ###   ########.fr       */
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
char	**split_args_and_find_bin(char **envp, char *cmd)
{
	char	**cmdas;
	char	*bin_og;
	char	*bin;

	cmdas = ft_split(cmd, ' ');
	if (!cmdas)
		perror_errno_and_exit(ENOMEM);
	bin_og = cmdas[0];
	bin = find_bin(envp, bin_og);
	if (!bin)
		perror_errno_and_exit(ENOENT);
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
t_list	*cmds_to_cmdas(t_list *cmds, char **envp)
{
	t_list	*cmds_og;

	cmds_og = cmds;
	while (cmds)
	{
		cmds->content = split_args_and_find_bin(envp, cmds->content);
		if (!cmds->content)
			perror_errno_and_exit(ENOMEM);
		cmds = cmds->next;
	}
	return (cmds_og);
}
