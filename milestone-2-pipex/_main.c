/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _main.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 16:08:58 by elagouch          #+#    #+#             */
/*   Updated: 2025/01/29 15:51:10 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/**
 * @brief	Entry point of the program
 */
int	main(int argc, char **argv, char **envp)
{
	ssize_t	fds[2];
	char	*file1;
	t_list	*cmdas;

	(void)argc;
	(void)argv;
	(void)envp;
	args_valid(argc, argv, (ssize_t *)fds);
	cmdas = populate_cmds(argc, argv, envp);
	ft_lstiter(cmdas, cmda_print);
	ft_lstclear(&cmdas, cmda_free);
	file1 = file_read(fds[0]);
	file_write(fds[1], file1);
	free(file1);
	return (0);
}
