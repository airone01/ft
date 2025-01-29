/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 18:46:10 by elagouch          #+#    #+#             */
/*   Updated: 2025/01/29 15:35:59 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/**
 * @brief	Populates the list of commands from the arguments
 */
static t_list	*populate_basic_cmds(int argc, char **argv)
{
	t_list	*cmds;
	t_list	*tmp;

	argc -= 3;
	argv += 2;
	cmds = NULL;
	while (argc--)
	{
		tmp = ft_lstnew(*argv);
		if (!tmp)
			perror_errno_and_exit(ENOMEM);
		if (!cmds)
			cmds = tmp;
		else
			ft_lstadd_back(&cmds, tmp);
		argv++;
	}
	return (cmds);
}

/**
 * Populates the list of commands from the arguments
 *
 * @param argc	Number of arguments
 * @param argv	Arguments
 * @param envp	Environment variables
 *
 * @returns		A list of commands
 *
 * @exception	ENOMEM if malloc fails
 */
t_list	*populate_cmds(int argc, char **argv, char **envp)
{
	t_list	*cmds;
	t_list	*cmdas;

	cmds = populate_basic_cmds(argc, argv);
	if (!cmds)
		perror_errno_and_exit(ENOMEM);
	cmdas = cmds_to_cmdas(cmds, envp);
	if (!cmdas)
		perror_errno_and_exit(ENOMEM);
	return (cmdas);
}
