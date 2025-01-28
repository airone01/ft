/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _main.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 16:08:58 by elagouch          #+#    #+#             */
/*   Updated: 2025/01/28 18:08:09 by elagouch         ###   ########.fr       */
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
	t_list	*cmds;

	(void)argc;
	(void)argv;
	(void)envp;
	args_valid(argc, argv, (ssize_t *)fds);
	cmds = ft_lstnew(NULL);
	ft_lstadd_back(&cmds, ft_lstnew(find_bin(envp, argv[2])));
	ft_lstadd_back(&cmds, ft_lstnew(find_bin(envp, argv[3])));
	ft_printf("cmd1: %s\n", ft_lstat(cmds, 1)->content);
	ft_printf("cmd2: %s\n", ft_lstat(cmds, 2)->content);
	ft_lstclear(&cmds, free);
	file1 = file_read(fds[0]);
	file_write(fds[1], file1);
	free(file1);
	return (0);
}
