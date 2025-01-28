/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _main.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 16:08:58 by elagouch          #+#    #+#             */
/*   Updated: 2025/01/28 16:17:12 by elagouch         ###   ########.fr       */
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
	char	*cmd1;
	char	*cmd2;

	(void)argc;
	(void)argv;
	(void)envp;
	args_valid(argc, argv, (ssize_t *)fds);
	cmd1 = find_bin(envp, argv[2]);
	ft_printf("cmd1: %s\n", cmd1);
	free(cmd1);
	cmd2 = find_bin(envp, argv[3]);
	ft_printf("cmd2: %s\n", cmd2);
	free(cmd2);
	file1 = file_read(fds[0]);
	file_write(fds[1], file1);
	free(file1);
	return (0);
}
