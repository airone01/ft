/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 12:05:19 by maximart          #+#    #+#             */
/*   Updated: 2025/06/20 19:55:14 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdbool.h>  // bool
# include <stdint.h>   // uint8_t
# include <sys/time.h> // struct timeval

/*******************************************************************************
 *                                    Macros                                   *
 ******************************************************************************/

# define RESET "\033[039m"
# define RED "\033[091m"
# define BLUE "\033[034m"
# define GREEN "\033[092m"
# define YELLOW "\033[093m"
# define CYAN "\033[36m"

// Valgrind mode :-)
# define WIN_H 480
# define WIN_W 640

// # define WIN_H 720
// # define WIN_W 1280

# define FPS_COUNTER_TEXT_HEIGHT 20
# define FPS_COUNTER_TEXT_WIDTH 80

# define BASE_MOVE_SPEED 5.0
# define BASE_ROT_SPEED 3.0

# define MAX_SPRITE_FRAMES 8
# define SPRITE_SCALE 0.7

// float.h is forbidden
# define DBL_MAX    1.7976931348623157E+308

/*******************************************************************************
 *                                    Enums                                    *
 ******************************************************************************/

typedef enum e_hit_sides
{
	SIDE_NORTH_SHOUTH = 1,
	SIDE_EAST_WEST = 0,
}					t_hit_sides;

typedef enum e_key
{
	ON_DESTROY = 17,
}					t_key;

typedef enum e_parse_state
{
	STATE_CONFIG,
	STATE_MAP,
	STATE_POST_MAP,
}					t_parse_state;

/*******************************************************************************
 *                                  Structures                                 *
 ******************************************************************************/

/*
** Raycasting implementation using DDA algorithm
** This is the core of the 3D rendering engine for cub3d
*/

typedef struct s_ray
{
	// Components of ray direction vector
	double			ray_dir_x;
	double			ray_dir_y;
	int				map_x;
	int				map_y;
	double			side_dist_x;
	double			side_dist_y;
	double			delta_dist_x;
	double			delta_dist_y;
	double			perp_wall_dist;

	double			horizontal_x;
	double			horizontal_y;
	double			vertical_x;
	double			vertical_y;
	double			horizontal_dist;
	double			vertical_dist;

	// Step dirs are -1 or 1
	int				step_x;
	int				step_y;
	// Flag
	bool			hit;
	// Which side was hit
	t_hit_sides		side;
	int				line_height;
	// Start and end Y positions
	int				draw_start;
	int				draw_end;
	/* Texture width */
	int				tex_x;
}					t_ray;

/*
** Player structure to handle position, direction, and movement
*/
typedef struct s_player
{
	/* Position */
	double			pos_x;
	double			pos_y;

	double			angle;
	/* Direction */
	/* Components of direction vector (where player is looking) */
	double			dir_x;
	double			dir_y;

	/* Camera plane */
	/* Components of camera plane (perpendicular to direction) */
	double			plane_x;
	double			plane_y;

	/* Movement */
	double			move_speed;
	double			rot_speed;

	/* Controls state */
	/* Those are all on/off flags */
	bool			move_forward;
	bool			move_backward;
	bool			move_left;
	bool			move_right;
	bool			rotate_left;
	bool			rotate_right;

	/* Screen properties */
	/* Camera height (usually screen_height/2) */
	double			cam_height;
}					t_player;

/*
** Texture structure to store image data
*/
typedef struct s_texture
{
	/* MLX inage */
	void			*img;
	/* Texture data */
	char			*addr;
	int				width;
	int				height;
	/* Other MLX info */
	int				bits_per_pixel;
	int				line_length;
	int				endian;
}					t_texture;

/*
** Structure to hold all textures
*/
typedef struct s_textures
{
	t_texture		north;
	t_texture		south;
	t_texture		east;
	t_texture		west;
	t_texture		door;
}					t_textures;

/*
** Info for the MLX stored here for convenience
*/
typedef struct s_img
{
	void			*img;
	char			*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
}					t_img;

/*
** Union type for easily manipulating color
** This is way more convenient than an unsigned integer.
** Also we're using uint8_t because we need a type of 8 bytes long of
*/
typedef union u_color
{
	unsigned int	val;
	struct
	{
		uint8_t		blue;
		uint8_t		green;
		uint8_t		red;
		uint8_t		alpha;
	};
}					t_color;

typedef struct s_map_buffer
{
	char			**lines;
	int				count;
	int				capacity;
	int				max_width;
}					t_map_buffer;

/*
** Door structs
*/
typedef struct s_door
{
	int				x;
	int				y;
	bool			open;
	bool			opening;
	bool			closing;
	float			prog;
}					t_door;

typedef struct s_door_system
{
	t_door			*doors;
	int				count;
	int				capacity;
	float			animation_speed;
}					t_door_system;

/*
** Sprite structs
*/
typedef struct s_sprite_animation
{
	t_texture	frames[MAX_SPRITE_FRAMES];
	int			frame_count;
	float		frame_duration;
	float		current_time;
	int			current_frame;
	bool		loop;
}	t_sprite_animation;

typedef struct s_sprite
{
	double				x;
	double				y;
	t_sprite_animation	animation;
	bool				active;
	double				distance;
	float				scale;
}	t_sprite;

typedef struct s_sprite_system
{
	t_sprite	*sprites;
	int			count;
	int			capacity;
	int			*render_order;
}	t_sprite_system;

/*
** Global application data
*/
typedef struct s_data
{
	char			**map;
	char			*map_file_path;
	int				error_detected;
	// Textures
	char			*texture_n;
	char			*texture_s;
	char			*texture_e;
	char			*texture_w;
	char			*texture_door;
	char			*texture_sprite;
	// MLX stuff
	t_img			img;
	void			*mlx;
	void			*win;
	// Sizes
	int				map_height;
	int				map_width;
	int				win_width;
	int				win_height;
	// Pointers
	t_player		player;
	t_textures		textures;
	// Colors
	t_color			floor_color;
	t_color			ceil_color;
	bool			color_f_found;
	bool			color_c_found;
	// Frame timing
	struct timeval	last_frame;
	struct timeval	current_frame;
	double			delta_time;
	double			fps;
	int				frame_count;
	double			fps_timer;
	double			time_accumulator;
	// Bonus/extra
	t_door_system	door_sys;
	t_sprite_system	sprite_sys;
	double			*z_buffer;
}					t_data;

// This is very specific
typedef struct s_double_int
{
	int				*x;
	int				*y;
}					t_double_int;

/*******************************************************************************
 *                             Function Prototypes                             *
 ******************************************************************************/

/*
** m_utils.c
*/

/**
 * @brief Checks for the validity of the arguments
 *
 * @param argc Arguments count
 * @param argv Arguments
 * @return true
 * @return false
 */
bool				check_args(int argc, char **argv);

#endif // !CUB3D_H