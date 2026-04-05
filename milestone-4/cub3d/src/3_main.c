/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 16:06:00 by maximart          #+#    #+#             */
/*   Updated: 2025/06/20 19:31:59 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"
#include "mem.h"
#include "mlx.h"
#include "parsing.h"
#include "player.h"
#include "pproc.h"
#include "utils.h"
#include "ft_printf.h"
#include <limits.h>

t_data	*init_data(void)
{
	t_data	*data;

	data = ft_calloc(1, sizeof(t_data));
	if (!data)
		return (NULL);
	data->error_detected = false;
	data->color_f_found = false;
	data->color_c_found = false;
	data->mlx = mlx_init();
	if (!data->mlx)
		return (free_resources(&data));
	data->win_width = WIN_W;
	data->win_height = WIN_H;
	data->z_buffer = ft_calloc((unsigned long)data->win_width, sizeof(double));
	if (!data->z_buffer)
		return (free_resources(&data));
	data->win = mlx_new_window(data->mlx, data->win_width, data->win_height,
			(char *)"~~~ kyubu kui ~~~");
	if (!data->win)
		return (free_resources(&data));
	data->img.img = mlx_new_image(data->mlx, data->win_width, data->win_height);
	data->img.addr = mlx_get_data_addr(data->img.img, &data->img.bits_per_pixel,
			&data->img.line_length, &data->img.endian);
	gettimeofday(&data->last_frame, NULL);
	return (data);
}

bool	check_error(int argc, char **argv)
{
	const char	*ptr;

	if (argc != 2)
	{
		ft_printf_fd(2, RED "Error\nUsage: %s <map_file>\n" RESET, argv[0]);
		return (true);
	}
	else
	{
		ptr = ft_strnstr(argv[1], ".cub", INT_MAX);
		if (!ptr || ptr[4] != '\0')
		{
			ft_printf(RED "Error\nInvalid extension\n" RESET);
			return (true);
		}
	}
	return (false);
}

int	main_color_resources(t_data *data)
{
	if (!data->color_c_found)
	{
		ft_printf(RED "Error\nColor C is empty\n" RESET);
		return (1);
	}
	if (!data->color_f_found)
	{
		ft_printf(RED "Error\nColor F is empty\n" RESET);
		return (1);
	}
	if (load_game_textures(data))
		return (1);
	return (0);
}

#ifdef __3DS__
# include <3ds.h>
# include <stdio.h>
extern void wait_for_exit();
# define DEBUG_LOG(msg) svcOutputDebugString(msg, ft_strlen(msg))
#else
# define DEBUG_LOG(msg)
#endif

int	main(int argc, char **argv)
{
	t_data	*data;
	char	*map_path;

	DEBUG_LOG("MAIN: Starting...\n");
#ifdef __3DS__
	if (R_FAILED(romfsInit())) {
        DEBUG_LOG("MAIN: Error: Failed to init ROMFS\n");
        printf("Error: Failed to init ROMFS\n");
        wait_for_exit();
        return (1);
    }
    DEBUG_LOG("MAIN: ROMFS Initialized.\n");
    printf("ROMFS: Initialized.\n");
	map_path = (char *)"romfs:/default.cub";
	(void)argc;
	(void)argv;
#else
	if (check_error(argc, argv))
		return (1);
	map_path = argv[1];
#endif
	data = init_data();
	if (!data) {
        DEBUG_LOG("MAIN: Error: init_data failed\n");
#ifdef __3DS__
        wait_for_exit();
#endif
		return (1);
    }
	data->map_file_path = ft_strdup(map_path);
	printf("MAIN: Loading map %s...\n", map_path);
    DEBUG_LOG("MAIN: Loading map...\n");
	if (!data->map_file_path || read_file(data, map_path)
		|| validate_config_completeness(data) || check_map_validity(data)
		|| main_color_resources(data))
	{
        DEBUG_LOG("MAIN: Error: Failed to load map or resources\n");
		printf("MAIN: Error: Failed to load map or resources.\n");
		free_resources(&data);
#ifdef __3DS__
        wait_for_exit();
		romfsExit();
#endif
		return (1);
	}
    DEBUG_LOG("MAIN: Resources loaded.\n");
	handle_main_bonus_features(data);
	init_player(data);
    DEBUG_LOG("MAIN: Setting up hooks...\n");
	setup_mlx_hooks(data);
    DEBUG_LOG("MAIN: Entering loop...\n");
	mlx_loop(data->mlx);
    DEBUG_LOG("MAIN: Exited loop.\n");
	free_resources(&data);
#ifdef __3DS__
	romfsExit();
#endif
	return (0);
}
