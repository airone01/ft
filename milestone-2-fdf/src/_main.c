/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _main.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 13:28:38 by elagouch          #+#    #+#             */
/*   Updated: 2025/02/21 22:56:46 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	manage_mlx(t_app *app)
{
	app->mlx = mlx_init();
	if (!app->mlx)
		exit_error(app, ERR_MLX_INIT);
	app->img.img = mlx_new_image(app->mlx, app->img.width, app->img.height);
	app->img.addr = mlx_get_data_addr(app->img.img, &app->img.bits_per_pixel,
			&app->img.line_length, &app->img.endian);
	app->win = mlx_new_window(app->mlx, IMG_WIDTH, IMG_HEIGHT,
			(char *)"r1's fdf");
	if (!app->win)
		exit_error(app, ERR_MLX_WINDOW);
	register_hooks(app);
	mlx_loop(app->mlx);
}

int	main(int argc, char **argv, char **envp)
{
	t_app	*app;
	char	*file;
	char	*tmp;

	(void)args_check(argc, argv);
	app = app_init();
	app->file_fd = file_open(argv[1], envp);
	file = read_entire_file(app->file_fd, (size_t *)&app->map.width);
	tmp = file;
	app->map.height = 1;
	while (*tmp)
	{
		if (*tmp == '\n')
			app->map.height++;
		tmp++;
	}
	app->map.matrix = allocate_matrix(app->map.width, app->map.height);
	map_parse(app, file);
	find_elevation_bounds(app);
	calculate_initial_scale(app);
	manage_mlx(app);
	app_clear(app);
	free(app->mlx);
	return (0);
}
