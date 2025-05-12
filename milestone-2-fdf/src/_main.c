/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _main.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 13:28:38 by elagouch          #+#    #+#             */
/*   Updated: 2025/05/12 02:19:02 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	manage_mlx(t_ctx *ctx)
{
	ctx->mlx = mlx_init();
	if (!ctx->mlx)
		exit_error(ctx, ERR_MLX_INIT);
	ctx->img.img = mlx_new_image(ctx->mlx, ctx->img.width, ctx->img.height);
	ctx->img.addr = mlx_get_data_addr(ctx->img.img, &ctx->img.bits_per_pixel,
			&ctx->img.line_length, &ctx->img.endian);
	ctx->win = mlx_new_window(ctx->mlx, IMG_WIDTH, IMG_HEIGHT,
			(char *)"r1's fdf");
	if (!ctx->win)
		exit_error(ctx, ERR_MLX_WINDOW);
	register_hooks(ctx);
	mlx_loop(ctx->mlx);
}

static void	find_map_height(t_ctx *ctx)
{
	char	**file;

	file = ctx->file_content;
	ctx->map.height = 0;
	while (*file && **file)
	{
		if (**file && **file != '\n')
			ctx->map.height++;
		file++;
	}
}

/**
 * @brief Finds the width of the map by counting columns in the first line
 *
 * @param ctx Context
 */
static void	find_map_width(t_ctx *ctx)
{
	int	count;

	if (!ctx->file_content || !ctx->file_content[0])
		exit_error(ctx, ERR_FILE_EMPTY);
	count = count_columns_in_line(ctx->file_content[0]);
	if (count <= 0)
		exit_error(ctx, ERR_MAP_EMPTY_LINE);
	ctx->map.width = count;
}

int	main(int argc, char **argv, char **envp)
{
	t_ctx	*ctx;
	int		fd;

	(void)args_check(argc, argv);
	fd = file_open(argv[1], envp);
	ctx = ctx_init();
	ctx->file_fd = fd;
	ctx->file_content = read_entire_file(ctx->file_fd);
	if (!ctx->file_content)
		exit_error(ctx, ERR_FILE_READ);
	if (!ctx->file_content[0])
		exit_error(ctx, ERR_FILE_EMPTY);
	find_map_width(ctx);
	find_map_height(ctx);
	ctx->map.matrix = allocate_matrix(ctx->map.width, ctx->map.height);
	if (!ctx->map.matrix)
		exit_error(ctx, ERR_MALLOC_MAP);
	map_parse(ctx);
	find_elevation_bounds(ctx);
	calculate_initial_scale(ctx);
	manage_mlx(ctx);
	ctx_clear(ctx);
	return (0);
}
