/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 13:28:52 by elagouch          #+#    #+#             */
/*   Updated: 2025/05/12 02:26:10 by elagouch         ###   ########.fr       */
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
}						t_error;

typedef struct s_map_point
{
	int					elevation;
	unsigned int		color;
}						t_map_point;

typedef struct s_map
{
	t_map_point			**matrix;
	int					width;
	int					height;
	int					min_elevation;
	int					max_elevation;
}						t_map;

typedef struct s_img
{
	void				*img;
	char				*addr;
	int					bits_per_pixel;
	int					line_length;
	int					endian;
	int					width;
	int					height;
}						t_img;

typedef enum e_projection_type
{
	PROJECTION_ISOMETRIC,
	PROJECTION_CABINET,
	PROJECTION_CONIC,
}						t_projection_type;

typedef struct s_ctx
{
	// Color scheme
	int					color_scheme;
	// MLX
	void				*mlx;
	void				*win;
	// File
	char				**file_content;
	int					file_fd;
	// Map
	t_map				map;
	// Rendering
	t_projection_type	projection_type;
	bool				needs_render;
	double				horizon_distance;
	t_img				img;
	// Rendering: Offsets
	double				offset_x;
	double				offset_y;
	// Rendering: Scales
	double				z_scale;
	double				scale;
	// Rendering: Rotations
	double				rot_x;
	double				rot_y;
	double				rot_z;
	// Rendering: LOD
	int					lod_level;
	// Rendering: Debug
	int					debug_mode;
}						t_ctx;

// Isometric point
typedef struct s_point
{
	double				x;
	double				y;
}						t_point;

typedef struct s_color_get_line_params
{
	t_ctx				*ctx;
	int					z1;
	int					z2;
	unsigned int		color1;
	unsigned int		color2;
}						t_color_get_line_params;

typedef struct s_connection_points
{
	t_point				current;
	t_point				down;
}						t_connection_points;

typedef struct s_connection_colors
{
	unsigned int		current;
	unsigned int		down;
}						t_connection_colors;

typedef struct s_connection_z
{
	int					current;
	int					down;
}						t_connection_z;

typedef struct s_connection_data
{
	t_point				current;
	t_point				down;
	unsigned int		current_color;
	unsigned int		down_color;
	int					current_z;
	int					down_z;
}						t_connection_data;

// Point in 3D space
typedef struct s_point3d
{
	double				x;
	double				y;
	double				z;
}						t_point3d;

typedef struct s_line_vars
{
	t_point				delta;
	t_point				current;
	double				steps;
}						t_line_vars;

enum					e_image
{
	IMG_WIDTH = 1920,
	IMG_HEIGHT = 1080,
};

// Keyboard keys
enum					e_keyboard
{
	// Letters
	KEY_A = 97,
	KEY_D = 100,
	KEY_E = 101,
	KEY_F = 102,
	KEY_G = 103,
	KEY_P = 112,
	KEY_Q = 113,
	KEY_R = 114,
	KEY_S = 115,
	KEY_T = 116,
	KEY_W = 119,
	// Arrows
	KEY_ARROW_UP = 65362,
	KEY_ARROW_DOWN = 65364,
	KEY_ARROW_LEFT = 65361,
	KEY_ARROW_RIGHT = 65363,
	// Numbers
	KEY_1 = 49,
	KEY_9 = 57,
	KEY_0 = 48,
	// After numbers
	KEY_EQUALS = 61,
	KEY_DASH = 45,
	// Numpad
	KEY_NUMPAD_PLUS = 65451,
	KEY_NUMPAD_MINUS = 65453,
	// Brackets
	KEY_SQUARE_BRACKET_OPENING = 91,
	KEY_SQUARE_BRACKET_CLOSING = 93,
	// Other
	KEY_ESCAPE = 65307,
	// Fn
	KEY_F1 = 65470,
	KEY_F2 = 65471,
	KEY_F3 = 65472,
	KEY_F4 = 65473,
	KEY_F5 = 65474,
	KEY_F6 = 65475,
	KEY_F7 = 65476,
};

// Colors
enum					e_colors
{
	BLACK = 0x00000000,
	WHITE = 0x00FFFFFF,
	RED = 0x00FF0000,
	GREEN = 0x0000FF00,
	BLUE = 0x000000FF,
};

/**
 * @brief Represents a rectangular section of the map
 */
typedef struct s_section
{
	int					start_x;
	int					start_y;
	int					end_x;
	int					end_y;
}						t_section;

typedef struct s_bresenham_params
{
	t_ctx				*ctx;
	int					*line;
	int					*params;
	unsigned int		color;
}						t_bresenham_params;

enum					e_lod_levels
{
	// Every point
	LOD_HIGH = 1,
	// Every second point
	LOD_MEDIUM = 2,
	// Every fourth point
	LOD_LOW = 4,
	// Every eighth point
	LOD_VERY_LOW = 8
};

/**
 * @brief Structure to hold rendering context for LOD connections
 */
typedef struct s_render_context
{
	t_ctx				*ctx;
	t_section			section;
	int					lod;
}						t_render_context;

/**
 * @brief Structure to hold rendering context for the render_section loop
 */
typedef struct s_render_section_params
{
	t_render_context	rc;
	t_section			section;
	bool				is_edge_x;
	bool				is_edge_y;
	t_ctx				*ctx;
	int					x;
	int					y;
}						t_render_section_params;

typedef enum e_debug_flags
{
	DEBUG_NONE = 0,
	DEBUG_SECTIONS = 1,
	DEBUG_LOD = 2
}						t_debug_flags;

// Global context structure
t_ctx					*ctx_init(void);

// Error handling
void					exit_error_free(t_ctx *ctx, t_error err, void *ptr);
void					exit_error(t_ctx *ctx, t_error err);
void					print_memory_error(t_error err);
void					print_math_error(t_error err);
void					print_file_error(t_error err);
void					print_arg_error(t_error err);
void					print_map_error(t_error err);
void					print_mlx_error(t_error err);

// Safety
void					*safe_recalloc(t_ctx *ctx, void *ptr,
							unsigned long old_size, unsigned long new_size);
void					*safe_calloc(t_ctx *ctx, unsigned long nmemb,
							size_t size);
void					free_2d_array(void **ptrs);
void					ctx_clear_0(t_ctx *ctx);
void					ctx_clear(t_ctx *ctx);

// Arguments handling
void					args_check(int argc, char **argv);

// File handling
int						file_open(char *path, char **envp);

// Map parsing
t_map_point				**allocate_matrix(int width, int height);
bool					parse_color(t_ctx *ctx, char *str, unsigned int *color);
void					parse_token(t_ctx *ctx, char *token, int row, int *col);
void					find_elevation_bounds(t_ctx *ctx);
void					map_parse(t_ctx *ctx);
int						count_columns_in_line(const char *line);

// Math
bool					fuzzy_equals(double a, double b);
int						fast_atoi(const char **str);

// Point mamipulation
t_point					get_projected_point(int x, int y, t_ctx *ctx);
t_point					point_lerp(t_point a, t_point b, double t);
t_point					point_rotate(t_point p, double angle);
t_point					point_scale(t_point p, double scale);
t_point					point_add(t_point a, t_point b);
t_point					point_sub(t_point a, t_point b);
t_point					point_normalize(t_point p);
double					point_distance(t_point a, t_point b);
double					point_dot(t_point a, t_point b);
double					point_magnitude(t_point p);

// Projection
t_point					conic_project(t_point3d p, t_ctx *ctx);
t_point					cabinet_project(t_point3d p);
t_point					iso_project(t_point3d p);

// Point3D manipulation
t_point3d				rotate_x(t_point3d p, double angle);
t_point3d				rotate_y(t_point3d p, double angle);
t_point3d				rotate_z(t_point3d p, double angle);

// MLX
void					mlx_pixel_put_img(t_img *img, int x, int y,
							unsigned int color);
void					key_hook(int keycode, t_ctx *ctx);
void					register_hooks(t_ctx *ctx);

// Rendering
void					draw_line_img(t_ctx *ctx, t_point start, t_point end,
							unsigned int color);
bool					prepare_right_connection(t_render_context *rc, int x,
							int y, t_connection_data *data);
bool					prepare_down_connection(t_render_context *rc, int x,
							int y, t_connection_data *data);
void					render_section(t_ctx *ctx, t_section section);
int						render_next_frame(t_ctx *ctx);
void					draw_lines(t_ctx *ctx);

// Rendering: Bresenham
void					process_point(t_ctx *ctx, int x, int y,
							unsigned int color);
void					process_x_step(t_bresenham_params p, int *x, int e2);
void					process_y_step(t_bresenham_params p, int *y, int e2);
bool					is_line_outside_bounds(t_ctx *ctx, int *line);

// Rendering optimization
bool					is_line_outside_viewport(t_point p1, t_point p2,
							int width, int height);
bool					is_section_outside_viewport(t_ctx *ctx,
							t_section section);
void					calculate_initial_scale(t_ctx *ctx);

// Rendering debug
void					draw_section_outline(t_ctx *ctx, t_section section,
							unsigned int color);
void					put_debug_number(t_ctx *ctx, double value, char *label,
							int y_pos);
int						append_double(char *str, double val, int max_len);
void					put_debug_text(t_ctx *ctx, char *msg, int y_pos);
int						append_int(char *str, int n, int max_len);
void					toggle_debug_mode(t_ctx *ctx, int flag);
void					render_section_debug(t_ctx *ctx);
void					render_lod_debug(t_ctx *ctx);

// Colors
unsigned int			color_get_by_scheme(int z, int min_z, int max_z,
							int scheme);
unsigned int			average_color(unsigned int c1, unsigned int c2);
unsigned int			color_get_line(t_color_get_line_params p);
unsigned int			hsv_to_rgb(double h, double s, double v);
unsigned int			color_get(int z, int min_z, int max_z);

#endif
