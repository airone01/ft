/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _main.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 13:28:38 by elagouch          #+#    #+#             */
/*   Updated: 2025/02/19 17:27:32 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

// static void	map_display(t_app *ctx)
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	while (i < ctx->map.height)
// 	{
// 		j = 0;
// 		while (j < ctx->map.width)
// 		{
// 			ft_printf("%d\t", ctx->map.matrix[i][j]);
// 			j++;
// 		}
// 		ft_printf("\n");
// 		i++;
// 	}
// }

void	my_mlx_pixel_put(t_img *img, int x, int y, unsigned int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

static void	manage_mlx(t_app *app)
{
	app->mlx = mlx_init();
	app->img.img = mlx_new_image(app->mlx, 1920, 1080);
	app->win = mlx_new_window(app->mlx, 1920, 1080, (char *)"r1's fdf");
	app->img.addr = mlx_get_data_addr(app->img.img, &app->img.bits_per_pixel,
			&app->img.line_length, &app->img.endian);
	my_mlx_pixel_put(&app->img, 5, 5, 0x00FF0000);
	mlx_put_image_to_window(app->mlx, app->win, app->img.img, 0, 0);
	mlx_loop(app->mlx);
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
	manage_mlx(app);
	app_clear(app);
	return (0);
}
