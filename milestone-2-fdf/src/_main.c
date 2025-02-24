/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _main.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 13:28:38 by elagouch          #+#    #+#             */
/*   Updated: 2025/02/24 16:17:14 by elagouch         ###   ########.fr       */
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

static void	find_map_height(t_app *app)
{
	char	**file;

	file = app->file_content;
	app->map.height = 0;
	while (*file && **file)
	{
		if (**file && **file != '\n')
			app->map.height++;
		file++;
	}
}

static void	find_map_width(t_app *app)
{
	char	*s;
	int		count;
	int		i;
	t_bool	was_space;

	i = 0;
	count = 0;
	s = app->file_content[0];
	was_space = true;
	while (s[i] && s[i] != '\n')
	{
		if (ft_isspace(s[i]))
		{
			was_space = true;
		}
		else if (was_space)
		{
			count++;
			was_space = false;
		}
		i++;
	}
	app->map.width = count;
}

int	main(int argc, char **argv, char **envp)
{
	t_app	*app;

	(void)args_check(argc, argv);
	app = app_init();
	app->file_fd = file_open(argv[1], envp);
	app->file_content = read_entire_file(app->file_fd);
	find_map_width(app);
	find_map_height(app);
	app->map.matrix = allocate_matrix(app->map.width, app->map.height);
	map_parse(app);
	find_elevation_bounds(app);
	calculate_initial_scale(app);
	manage_mlx(app);
	app_clear(app);
	return (0);
}
