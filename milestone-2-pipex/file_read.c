/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_read.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 17:31:26 by elagouch          #+#    #+#             */
/*   Updated: 2025/01/28 15:58:19 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/**
 * @brief	Read the whole file
 *
 * @param	fd	A valid file descriptor
 */
char	*file_read(ssize_t fd)
{
	char	*file;
	char	*tmp;
	char	*new_file;

	file = ft_strdup("");
	if (!file)
		perror_errno_and_exit(ENOMEM);
	tmp = get_next_line(fd);
	while (tmp)
	{
		new_file = ft_strjoin(file, tmp);
		free(file);
		free(tmp);
		if (!new_file)
			perror_errno_and_exit(ENOMEM);
		file = new_file;
		tmp = get_next_line(fd);
	}
	return (file);
}
