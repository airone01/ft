/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 13:28:52 by elagouch          #+#    #+#             */
/*   Updated: 2025/02/20 12:29:56 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "../extra-minilibx/mlx.h"                      // GPM!
# include "../milestone-0-libft/libft.h"                 // GPM!
# include "../milestone-1-ft_printf/ft_printf.h"         // GPM!
# include "../milestone-1-get_next_line/get_next_line.h" // GPM!
# include <errno.h>
# include <error.h>
# include <fcntl.h>
# include <limits.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>

# ifndef MAX_MAP_HEIGHT
#  define MAX_MAP_HEIGHT 1000
# endif

# ifndef DBL_EPSILON
#  define DBL_EPSILON 2.2204460492503131e-16
# endif

typedef enum e_error
{
	ERR_NONE = 0,
	ERR_ARG_COUNT = 1,
	ERR_ARG_INVALID_FILE = 2,
	ERR_FILE_OPEN = 10,
	ERR_FILE_READ = 11,
	ERR_FILE_EXTENSION = 12,
	ERR_FILE_EMPTY = 13,
	ERR_MALLOC = 20,
	ERR_MALLOC_MAP = 21,
	ERR_MALLOC_LINE = 22,
	ERR_MAP_INVALID_CHAR = 30,
	ERR_MAP_IRREGULAR = 31,
	ERR_MAP_TOO_LARGE = 32,
	ERR_MAP_EMPTY_LINE = 33,
	ERR_MAP_INVALID_COLOR = 34,
	ERR_MLX_INIT = 40,
	ERR_MLX_WINDOW = 41,
	ERR_MLX_IMAGE = 42,
	ERR_MATRIX_OVERFLOW = 50,
	ERR_INVALID_ROTATION = 51,
	ERR_INVALID_SCALE = 52,
	ERR_INVALID_PROJECTION = 53,
}			t_error;

typedef struct s_map
{
	int		**matrix;
	int		width;
	int		height;
}			t_map;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		width;
	int		height;
}			t_img;

typedef struct s_app
{
	t_map	map;
	t_img	img;
	void	*mlx;
	void	*win;
	int		file_fd;
}			t_app;

// Isometric point
typedef struct s_point
{
	double	x;
	double	y;
}			t_point;

// Point in 3D space
typedef struct s_point3d
{
	double	x;
	double	y;
	double	z;
}			t_point3d;

typedef struct s_line_vars
{
	t_point	delta;
	t_point	current;
	double	steps;
}			t_line_vars;

enum		e_image
{
	IMG_WIDTH = 1920,
	IMG_HEIGHT = 1080,
};

// Keyboard keys
enum		e_keyboard
{
	W = 119,
	S = 115,
	D = 100,
	A = 97,
	ESC = 65307,
};

// Colors
enum		e_colors
{
	BLACK = 0x00000000,
	WHITE = 0x00FFFFFF,
	RED = 0x00FF0000,
	GREEN = 0x0000FF00,
	BLUE = 0x000000FF,
};

// Global app structure
t_app		*app_init(void);

// Error handling
void		exit_error_free(t_app *ctx, t_error err, void *ptr);
void		exit_error(t_app *ctx, t_error err);
void		print_memory_error(t_error err);
void		print_math_error(t_error err);
void		print_file_error(t_error err);
void		print_arg_error(t_error err);
void		print_map_error(t_error err);
void		print_mlx_error(t_error err);

// Safety
void		*safe_calloc(t_app *ctx, unsigned long nmemb, size_t size);
void		*safe_recalloc(t_app *ctx, void *ptr, unsigned long old_size,
				unsigned long new_size);
void		free_2d_array(void **ptrs);
void		app_clear(t_app *ctx);

// Arguments handling
void		args_check(int argc, char **argv);

// File handling
void		file_sizes(t_app *ctx, char *file_path, char **envp);
int			file_open(char *path, char **envp);

// Map handling
void		read_map_data(t_app *ctx);

// Math
t_bool		fuzzy_equals(double a, double b);

// Point mamipulation
t_point		point_add(t_point a, t_point b);
double		point_distance(t_point a, t_point b);
double		point_dot(t_point a, t_point b);
t_point		iso_project(t_point3d p);
t_point		point_lerp(t_point a, t_point b, double t);
double		point_magnitude(t_point p);
t_point		point_normalize(t_point p);
t_point		point_rotate(t_point p, double angle);
t_point		point_scale(t_point p, double scale);
t_point		point_sub(t_point a, t_point b);

// MLX
void		my_mlx_pixel_put(t_img *img, int x, int y, unsigned int color);
void		my_draw_line_img(t_app *ctx, t_point start, t_point end,
				unsigned int color);
void		my_mlx_hooks(t_app *app);

#endif
