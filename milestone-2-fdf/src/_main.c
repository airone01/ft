/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _main.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 13:28:38 by elagouch          #+#    #+#             */
/*   Updated: 2025/02/21 10:31:56 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	map_display(t_app *ctx)
{
	int	i;
	int	j;

	i = 0;
	while (i < ctx->map.height)
	{
		j = 0;
		while (j < ctx->map.width)
		{
			ft_printf("%d\t", ctx->map.matrix[i][j]);
			j++;
		}
		ft_printf("\n");
		i++;
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_app	*app;

	(void)args_check(argc, argv);
	app = app_init();
	app->file_fd = file_open(argv[1], envp);
	file_sizes(app, argv[1], envp);
	app->map.matrix = safe_calloc(app, (unsigned long)app->map.height,
			sizeof(int *));
	read_map_data(app);
	map_display(app);
	app_clear(app);
	return (0);
}
