/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 15:52:39 by elagouch          #+#    #+#             */
/*   Updated: 2025/01/31 16:38:46 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/**
 * Handles the here_doc feature
 *
 * @param	limiter	The limiter string
 *
 * @returns	The file descriptor of the pipe
 */
int	handle_here_doc(t_app *app, char *limiter)
{
	char	*line;

	if (pipe(app->bonus_pipes) == -1)
		app_exit(*app);
	while (1)
	{
		line = get_next_line(STDIN_FILENO);
		if (!line)
		{
			ft_printf("[DEBUG] No line\n");
			break ;
		}
		if (ft_strncmp(line, limiter, ft_strlen(line) - 1) == 0)
		{
			free(line);
			break ;
		}
		write(app->bonus_pipes[1], line, ft_strlen(line));
		free(line);
	}
	close(app->bonus_pipes[1]);
	return (app->bonus_pipes[0]);
}
