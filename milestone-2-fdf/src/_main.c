/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _main.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 13:28:38 by elagouch          #+#    #+#             */
/*   Updated: 2025/02/19 12:55:34 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

static void	map_display(t_app *app)
{
	int	i;
	int	j;

	i = 0;
	while (i < app->map.height)
	{
		j = 0;
		while (j < app->map.width)
		{
			ft_printf("%d ", app->map.matrix[i][j]);
			j++;
		}
		ft_printf("\n");
		i++;
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_app	*app;
	int		fd;

	(void)args_check(argc, argv);
	fd = file_open(argv[1], envp);
	app = app_init();
	app->file_fd = fd;
	file_sizes(app, argv[1], envp);
	read_map_data(app, fd);
	map_display(app);
	app_clear(app);
	return (0);
}
