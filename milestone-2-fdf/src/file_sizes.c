/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_sizes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 11:48:51 by elagouch          #+#    #+#             */
/*   Updated: 2025/02/13 14:23:02 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

static int	count_words(char *line)
{
	int		words;
	int		i;

	words = 0;
	i = 0;
	while (line[i])
	{
		while (line[i] && ft_isspace(line[i]))
			i++;
		if (line[i])
			words++;
		while (line[i] && !ft_isspace(line[i]))
			i++;
	}
	return (words);
}

/**
 * Counts height and width of a map file
 *
 * @param app	The application context
 * @param path	The path to the file
 */
void	file_sizes(t_app *app, char *file_path, char **envp)
{
	char	*line;
	int		words;

	while (1)
	{
		line = get_next_line(app->file_fd);
		if (!line)
			break ;
		words = count_words(line);
		if (words != 0) {
			app->map.height++;
			if (app->map.width == -1)
				app->map.width = words;
			else if (app->map.width != words)
				exit_error(app, ERR_MAP_IRREGULAR);
		}
		free(line);
	}
	if (app->map.height == 0)
		exit_error(app, ERR_FILE_EMPTY);
	app->map.height++;
	close(app->file_fd);
	app->file_fd = file_open(file_path, envp);
}
