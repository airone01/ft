/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app_clear.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 16:38:41 by elagouch          #+#    #+#             */
/*   Updated: 2025/02/19 13:37:08 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

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
	if (!app)
		return ;
	if (app->file_fd >= 2)
		close(app->file_fd);
	clear_matrix(app);
	free(app);
}
