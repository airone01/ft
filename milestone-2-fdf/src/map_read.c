/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_read.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 09:51:00 by elagouch          #+#    #+#             */
/*   Updated: 2025/02/13 16:40:10 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

static int	*multi_atoi(t_app *app, char **split)
{
	int		*row;
	int		i;

	row = safe_calloc(app, (unsigned long)app->map.width, sizeof(int));
	i = 0;
	while (i < app->map.width)
	{
		row[i] = ft_atoi(split[i]);
		i++;
	}
	return (row);
}

static char	**split_line(t_app *app, char *line)
{
	char	**split;
	int		i;

	split = ft_split(line, ' ');
	if (!split)
		exit_error(app, ERR_MALLOC_LINE);
	i = 0;
	while (split[i])
		i++;
	i--;
	if (app->map.width != i)
	{
		ft_printf("i: %d\n", i);
		exit_error(app, ERR_MAP_IRREGULAR);
	}
	return (split);
}

/**
 * @brief Read the map from the file descriptor
 *
 * @param app	The application context
 * @param fd	The file descriptor to read from
 */
void	map_read(t_app *app, int fd)
{
	char	**strs;
	char	*line;
	int		i;

	app->map.matrix = safe_calloc(app, (unsigned long)app->map.height + 1, sizeof(int *));
	i = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (!line[0])
		{
			free(line);
			break ;
		}
		strs = split_line(app, line);
		free(line);
		app->map.matrix[i++] = multi_atoi(app, strs);
		free_ptrs(strs);
	}
	app->map.matrix[i] = NULL;
	app->map.height = i;
	line = get_next_line(fd);
	if (line)
	{
		free(line);
		exit_error(app, ERR_MAP_EMPTY_LINE);
	}
}
