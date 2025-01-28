/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _main.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 16:08:58 by elagouch          #+#    #+#             */
/*   Updated: 2025/01/28 18:29:48 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/**
 * @brief	Populates the list of commands from the arguments
 */
static t_list	*populate_cmds(int argc, char **argv, char **envp)
{
	t_list	*cmds;
	t_list	*tmp;

	argc -= 3;
	argv += 2;
	cmds = NULL;
	while (argc--)
	{
		tmp = ft_lstnew(find_bin(envp, *argv));
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

static void	cmd_print(void *content)
{
	char	*cmd;

	cmd = (char *)content;
	printf("cmd: %s\n", (char *)cmd);
}

/**
 * @brief	Entry point of the program
 */
int	main(int argc, char **argv, char **envp)
{
	ssize_t	fds[2];
	char	*file1;
	t_list	*cmds;

	(void)argc;
	(void)argv;
	(void)envp;
	args_valid(argc, argv, (ssize_t *)fds);
	cmds = ft_lstnew(NULL);
	cmds = populate_cmds(argc, argv, envp);
	ft_lstiter(cmds, cmd_print);
	ft_lstclear(&cmds, free);
	file1 = file_read(fds[0]);
	file_write(fds[1], file1);
	free(file1);
	return (0);
}
