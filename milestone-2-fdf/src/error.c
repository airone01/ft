/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 16:27:48 by elagouch          #+#    #+#             */
/*   Updated: 2025/02/19 12:13:23 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

/**
 * @brief Frees a pointer, and exits the program with an error message
 *
 * @param app	The app structure
 * @param err	The error code
 */
void	exit_error_free(t_app *app, t_error err, void *ptr)
{
	if (ptr)
		free(ptr);
	exit_error(app, err);
}

/**
 * @brief Exits the program with an error message
 *
 * @param app	The app structure
 * @param err	The error code
 */
void	exit_error(t_app *app, t_error err)
{
	if (app)
		app_clear(app);
	ft_printf("Error: ");
	if (err >= ERR_ARG_COUNT && err <= ERR_ARG_INVALID_FILE)
		print_arg_error(err);
	else if (err >= ERR_FILE_OPEN && err <= ERR_FILE_EMPTY)
		print_file_error(err);
	else if (err >= ERR_MALLOC && err <= ERR_MALLOC_LINE)
		print_memory_error(err);
	else if (err >= ERR_MAP_INVALID_CHAR && err <= ERR_MAP_INVALID_COLOR)
		print_map_error(err);
	else if (err >= ERR_MLX_INIT && err <= ERR_MLX_IMAGE)
		print_mlx_error(err);
	else if (err >= ERR_MATRIX_OVERFLOW && err <= ERR_INVALID_PROJECTION)
		print_math_error(err);
	exit((int)err);
}
