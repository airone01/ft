/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 13:28:52 by elagouch          #+#    #+#             */
/*   Updated: 2025/02/24 16:39:46 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

// This enables the use of M_PI
# define _USE_MATH_DEFINES

# include "ft_printf.h"
# include "get_next_line.h"
# include "libft.h"
# include "mlx.h"
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

# ifndef DBL_MAX
#  define DBL_MAX 1.7976931348623157e+308
# endif

# ifndef M_PI
#  define M_PI 3.14159265358979323846
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
}				t_error;

typedef struct s_map
{
	int			**matrix;
	int			width;
	int			height;
	int			min_elevation;
	int			max_elevation;
}				t_map;

typedef struct s_img
{
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	int			width;
	int			height;
}				t_img;

typedef struct s_app
{
	t_bool		needs_render;
	double		offset_x;
	double		offset_y;
	double		z_scale;
	double		scale;
	double		rot_x;
	double		rot_y;
	double		rot_z;
	t_map		map;
	t_img		img;
	char		**file_content;
	void		*mlx;
	void		*win;
	int			color_scheme;
	int			file_fd;
}				t_app;

// Isometric point
typedef struct s_point
{
	double		x;
	double		y;
}				t_point;

// Point in 3D space
typedef struct s_point3d
{
	double		x;
	double		y;
	double		z;
}				t_point3d;

typedef struct s_line_vars
{
	t_point		delta;
	t_point		current;
	double		steps;
}				t_line_vars;

enum			e_image
{
	IMG_WIDTH = 1920,
	IMG_HEIGHT = 1080,
};

// Keyboard keys
enum			e_keyboard
{
	KEY_W = 119,
	KEY_S = 115,
	KEY_D = 100,
	KEY_A = 97,
	KEY_Q = 113,
	KEY_E = 101,
	KEY_R = 114,
	KEY_T = 116,
	KEY_F = 102,
	KEY_G = 103,
	KEY_ARROW_UP = 65362,
	KEY_ARROW_DOWN = 65364,
	KEY_ARROW_LEFT = 65361,
	KEY_ARROW_RIGHT = 65363,
	KEY_EQUALS = 61,
	KEY_DASH = 45,
	KEY_NUMPAD_PLUS = 65451,
	KEY_NUMPAD_MINUS = 65453,
	KEY_SQUARE_BRACKET_OPENING = 91,
	KEY_SQUARE_BRACKET_CLOSING = 93,
	KEY_ESCAPE = 65307,
	KEY_1 = 49,
};

// Colors
enum			e_colors
{
	BLACK = 0x00000000,
	WHITE = 0x00FFFFFF,
	RED = 0x00FF0000,
	GREEN = 0x0000FF00,
	BLUE = 0x000000FF,
};

// Global app structure
t_app			*app_init(void);

// Error handling
void			exit_error_free(t_app *ctx, t_error err, void *ptr);
void			exit_error(t_app *ctx, t_error err);
void			print_memory_error(t_error err);
void			print_math_error(t_error err);
void			print_file_error(t_error err);
void			print_arg_error(t_error err);
void			print_map_error(t_error err);
void			print_mlx_error(t_error err);

// Safety
void			*safe_recalloc(t_app *ctx, void *ptr, unsigned long old_size,
					unsigned long new_size);
void			*safe_calloc(t_app *ctx, unsigned long nmemb, size_t size);
void			free_2d_array(void **ptrs);
int				app_clear_0(t_app *app);
void			app_clear(t_app *ctx);

// Arguments handling
void			args_check(int argc, char **argv);

// File handling
void			file_sizes(t_app *ctx, char *file_path, char **envp);
int				file_open(char *path, char **envp);

// Map handling
void			map_parse(t_app *app);
void			find_elevation_bounds(t_app *ctx);
int				**allocate_matrix(int width, int height);

// Math
t_bool			fuzzy_equals(double a, double b);
int				fast_atoi(const char **str);

// Point mamipulation
t_point			point_add(t_point a, t_point b);
double			point_distance(t_point a, t_point b);
double			point_dot(t_point a, t_point b);
t_point			iso_project(t_point3d p);
t_point			point_lerp(t_point a, t_point b, double t);
double			point_magnitude(t_point p);
t_point			point_normalize(t_point p);
t_point			point_rotate(t_point p, double angle);
t_point			point_scale(t_point p, double scale);
t_point			point_sub(t_point a, t_point b);

// Point3D manipulation
t_point3d		rotate_x(t_point3d p, double angle);
t_point3d		rotate_y(t_point3d p, double angle);
t_point3d		rotate_z(t_point3d p, double angle);

// MLX
void			mlx_pixel_put_img(t_img *img, int x, int y, unsigned int color);
int				key_hook(int keycode, t_app *app);
void			register_hooks(t_app *app);

// Rendering
void			draw_line_img(t_app *ctx, t_point start, t_point end,
					unsigned int color);
void			calculate_initial_scale(t_app *app);
int				render_next_frame(t_app *app);

// Colors
unsigned int	color_get_by_scheme(int z, int min_z, int max_z, int scheme);
unsigned int	color_get_line(t_app *ctx, int z1, int z2);
unsigned int	hsv_to_rgb(double h, double s, double v);
unsigned int	color_get(int z, int min_z, int max_z);

#endif
