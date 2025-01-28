/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_valid.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 17:32:34 by elagouch          #+#    #+#             */
/*   Updated: 2025/01/28 18:17:58 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/**
 * @brief	Check if the arguments are valid
 *
 * @param	argc	Number of arguments
 * @param	argv	Arguments
 * @param	fds		File descriptors (assumig are 2)
 */
void	args_valid(size_t argc, char **argv, ssize_t *fds)
{
	if (argc < 5)
		perror_errno_and_exit(EINVAL);
	if (argc >= PIPEX_PIPES_MAX + 4)
		perror_errno_and_exit(E2BIG);
	fds[0] = open(argv[1], O_RDONLY);
	if (fds[0] == -1)
		perror_and_exit();
	fds[1] = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fds[1] == -1)
	{
		close(fds[0]);
		perror_and_exit();
	}
}
