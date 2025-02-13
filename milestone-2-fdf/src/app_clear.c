/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app_clear.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 16:38:41 by elagouch          #+#    #+#             */
/*   Updated: 2025/02/13 16:34:04 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

static void	clear_matrix(t_app *app)
{
	int	i;

	i = 0;
	if (app->map.matrix)
	{
		while (app->map.matrix[i])
		{
			free(app->map.matrix[i]);
			app->map.matrix[i] = NULL;
			i++;
		}
		free(app->map.matrix);
		app->map.matrix = NULL;
	}
}

void	app_clear(t_app *app)
{
	if (!app)
		return ;
	if (app->file_fd >= 2)
		close(app->file_fd);
	clear_matrix(app);
	free(app);
}
