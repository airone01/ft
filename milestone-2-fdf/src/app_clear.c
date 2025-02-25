/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app_clear.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 16:38:41 by elagouch          #+#    #+#             */
/*   Updated: 2025/02/25 09:11:40 by elagouch         ###   ########.fr       */
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

void	app_clear(t_app *ctx)
{
	void	*mlx_ptr;

	if (!ctx)
		return ;
	mlx_ptr = ctx->mlx;
	if (ctx->file_fd >= 2)
		close(ctx->file_fd);
	clear_matrix(ctx);
	if (mlx_ptr)
	{
		if (ctx->img.img)
			mlx_destroy_image(mlx_ptr, ctx->img.img);
		if (ctx->win)
			mlx_destroy_window(mlx_ptr, ctx->win);
	}
	if (ctx->file_content)
		free_2d_array((void **)ctx->file_content);
	free(ctx);
	if (mlx_ptr)
	{
		mlx_destroy_display(mlx_ptr);
		free(mlx_ptr);
	}
}
