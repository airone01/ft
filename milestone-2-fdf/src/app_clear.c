/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app_clear.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 16:38:41 by elagouch          #+#    #+#             */
/*   Updated: 2025/02/21 19:17:58 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	clear_matrix(t_app *ctx)
{
	int	i;

	i = 0;
	if (ctx->map.matrix)
	{
		while (i < ctx->map.height)
		{
			free(ctx->map.matrix[i]);
			ctx->map.matrix[i] = NULL;
			i++;
		}
		free(ctx->map.matrix);
		ctx->map.matrix = NULL;
	}
}

void	app_clear(t_app *app)
{
	void	*mlx_ptr;

	if (!app)
		return ;
	mlx_ptr = app->mlx;
	if (app->file_fd >= 2)
		close(app->file_fd);
	clear_matrix(app);
	if (mlx_ptr)
	{
		if (app->img.img)
			mlx_destroy_image(mlx_ptr, app->img.img);
		if (app->win)
			mlx_destroy_window(mlx_ptr, app->win);
	}
	free(app);
	if (mlx_ptr)
	{
		mlx_destroy_display(mlx_ptr);
		free(mlx_ptr);
	}
}
