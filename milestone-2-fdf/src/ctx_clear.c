/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctx_clear.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 16:38:41 by elagouch          #+#    #+#             */
/*   Updated: 2025/05/12 02:15:59 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	clear_matrix(t_ctx *ctx)
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

void	ctx_clear(t_ctx *ctx)
{
	if (!ctx)
		return ;
	if (ctx->file_fd >= 2)
		close(ctx->file_fd);
	clear_matrix(ctx);
	if (ctx->mlx)
	{
		if (ctx->img.img)
			mlx_destroy_image(ctx->mlx, ctx->img.img);
		if (ctx->win)
			mlx_destroy_window(ctx->mlx, ctx->win);
	}
	if (ctx->file_content)
		free_2d_array((void **)ctx->file_content);
	if (ctx->mlx)
	{
		mlx_destroy_display(ctx->mlx);
		free(ctx->mlx);
	}
	free(ctx);
}
