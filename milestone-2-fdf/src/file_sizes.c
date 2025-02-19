/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_sizes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 11:48:51 by elagouch          #+#    #+#             */
/*   Updated: 2025/02/19 13:58:48 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

static int	count_words(char *line)
{
	int	words;
	int	i;

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
 * @param ctx	The application context
 * @param path	The path to the file
 */
void	file_sizes(t_app *ctx, char *file_path, char **envp)
{
	char	*line;
	int		words;

	while (1)
	{
		line = get_next_line(ctx->file_fd);
		if (!line)
			break ;
		words = count_words(line);
		if (words != 0)
		{
			ctx->map.height++;
			if (ctx->map.width == -1)
				ctx->map.width = words;
			else if (ctx->map.width != words)
				exit_error_free(ctx, ERR_MAP_IRREGULAR, line);
		}
		free(line);
	}
	if (ctx->map.width <= 0)
		exit_error(ctx, ERR_FILE_EMPTY);
	ctx->map.height++;
	close(ctx->file_fd);
	ctx->file_fd = file_open(file_path, envp);
}
