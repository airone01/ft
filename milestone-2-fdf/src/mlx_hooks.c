/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 18:23:05 by elagouch          #+#    #+#             */
/*   Updated: 2025/02/20 12:04:41 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

int	close_hook(t_app *app)
{
	app_clear(app);
	exit(0);
}

int	key_hook(int key, t_app *app)
{
	if (key == ESC)
	{
		app_clear(app);
		exit(0);
	}
	return (0);
}

void	my_mlx_hooks(t_app *app)
{
	mlx_hook(app->win, 2, 1L << 0, key_hook, app);
	mlx_hook(app->win, 17, 0, close_hook, app);
}
