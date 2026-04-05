#include "mlx.h"
#include "player.h"
#include <3ds.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// Helper for Citra/Emulator logging
static void	debug_log(const char *msg)
{
	svcOutputDebugString(msg, strlen(msg));
}

// 3DS Top Screen is 400x240
#define SCREEN_WIDTH 400
#define SCREEN_HEIGHT 240

typedef struct s_3ds_img
{
	int				width;
	int				height;
	char			*data;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
}					t_3ds_img;

typedef struct s_3ds_mlx
{
	int				(*loop_hook)(void *);
	void			*loop_param;
	void			*key_press_hook;
	void			*key_press_param;
	void			*key_release_hook;
	void			*key_release_param;
	void			*destroy_hook;
	void			*destroy_param;
}					t_3ds_mlx;

// Global mlx_ptr for hooks that don't pass it
void				*g_mlx_ptr = NULL;

void	wait_for_exit(void)
{
	printf("\nPress START to exit...\n");
	debug_log("Wait for exit...\n");
	while (aptMainLoop())
	{
		hidScanInput();
		if (hidKeysDown() & KEY_START)
			break ;
		gfxFlushBuffers();
		gfxSwapBuffers();
		gspWaitForVBlank();
	}
}

void	*mlx_init(void)
{
	t_3ds_mlx	*mlx;

	gfxInitDefault();
	consoleInit(GFX_BOTTOM, NULL);
	debug_log("MLX: Initializing 3DS shim...\n");
	printf("MLX: Initializing 3DS shim...\n");
	mlx = malloc(sizeof(t_3ds_mlx));
	if (!mlx)
	{
		debug_log("MLX: Error: malloc failed for mlx_ptr\n");
		printf("MLX: Error: malloc failed for mlx_ptr\n");
		return (NULL);
	}
	memset(mlx, 0, sizeof(t_3ds_mlx));
	g_mlx_ptr = mlx;
	debug_log("MLX: Initialized.\n");
	printf("MLX: Initialized.\n");
	return (mlx);
}

void	*mlx_new_window(void *mlx_ptr, int size_x, int size_y, char *title)
{
	(void)mlx_ptr;
	(void)size_x;
	(void)size_y;
	(void)title;
	return ((void *)1); // dummy
}

void	*mlx_new_image(void *mlx_ptr, int width, int height)
{
	t_3ds_img	*img;

	(void)mlx_ptr;
	img = malloc(sizeof(t_3ds_img));
	img->width = width;
	img->height = height;
	img->bits_per_pixel = 32;
	img->line_length = width * 4;
	img->endian = 0;
	img->data = malloc(width * height * 4);
	memset(img->data, 0, width * height * 4);
	return (img);
}

char	*mlx_get_data_addr(void *img_ptr, int *bits_per_pixel, int *size_line,
		int *endian)
{
	t_3ds_img	*img;

	img = (t_3ds_img *)img_ptr;
	if (!img)
		return (NULL);
	*bits_per_pixel = img->bits_per_pixel;
	*size_line = img->line_length;
	*endian = img->endian;
	return (img->data);
}

int	mlx_put_image_to_window(void *mlx_ptr, void *win_ptr, void *img_ptr, int x,
		int y)
{
	t_3ds_img	*img;
	u8			*fb;
	int			src_idx;
	int			x_phys;
	int			y_phys;
	int			dst_idx;

	(void)mlx_ptr;
	(void)win_ptr;
	(void)x;
	(void)y;
	img = (t_3ds_img *)img_ptr;
	if (!img || !img->data)
		return (0);
	fb = gfxGetFramebuffer(GFX_TOP, GFX_LEFT, NULL, NULL);
	// Screen is 240x400 physically (portrait),
		but we use it as 400x240 (landscape)
	// x' = 239 - y
	// y' = x
	for (int j = 0; j < SCREEN_HEIGHT && j < img->height; j++)
	{
		for (int i = 0; i < SCREEN_WIDTH && i < img->width; i++)
		{
			src_idx = (j * img->width + i) * 4;
			x_phys = 239 - j;
			y_phys = i;
			dst_idx = (x_phys + y_phys * 240) * 3;
			// fb is BGR
			fb[dst_idx] = img->data[src_idx + 0];     // B
			fb[dst_idx + 1] = img->data[src_idx + 1]; // G
			fb[dst_idx + 2] = img->data[src_idx + 2]; // R
		}
	}
	return (0);
}

int	mlx_loop(void *mlx_ptr)
{
	t_3ds_mlx	*mlx;
	u32			kDown;
	u32			kUp;
	int			(*func)(int, void *);
	int			(*func)(int, void *);
	int			(*func)(void *);

	mlx = (t_3ds_mlx *)mlx_ptr;
	while (aptMainLoop())
	{
		hidScanInput();
		kDown = hidKeysDown();
		kUp = hidKeysUp();
		if (mlx->key_press_hook)
		{
			(func)(int, void ) = (int (*)(int, void *))mlx->key_press_hook;
			if (kDown & KEY_START)
				func(ESCAPE, mlx->key_press_param);
			if (kDown & KEY_DUP)
				func(W, mlx->key_press_param);
			if (kDown & KEY_DDOWN)
				func(S, mlx->key_press_param);
			if (kDown & KEY_DLEFT)
				func(A, mlx->key_press_param);
			if (kDown & KEY_DRIGHT)
				func(D, mlx->key_press_param);
			if (kDown & KEY_L)
				func(LEFT_ARROW, mlx->key_press_param);
			if (kDown & KEY_R)
				func(RIGHT_ARROW, mlx->key_press_param);
			if (kDown & KEY_A)
				func(W, mlx->key_press_param);
			if (kDown & KEY_B)
				func(S, mlx->key_press_param);
			if (kDown & KEY_Y)
				func(A, mlx->key_press_param);
			if (kDown & KEY_X)
				func(D, mlx->key_press_param);
		}
		if (mlx->key_release_hook)
		{
			(func)(int, void ) = (int (*)(int, void *))mlx->key_release_hook;
			if (kUp & KEY_DUP)
				func(W, mlx->key_release_param);
			if (kUp & KEY_DDOWN)
				func(S, mlx->key_release_param);
			if (kUp & KEY_DLEFT)
				func(A, mlx->key_release_param);
			if (kUp & KEY_DRIGHT)
				func(D, mlx->key_release_param);
			if (kUp & KEY_L)
				func(LEFT_ARROW, mlx->key_release_param);
			if (kUp & KEY_R)
				func(RIGHT_ARROW, mlx->key_release_param);
			if (kUp & KEY_A)
				func(W, mlx->key_release_param);
			if (kUp & KEY_B)
				func(S, mlx->key_release_param);
			if (kUp & KEY_Y)
				func(A, mlx->key_release_param);
			if (kUp & KEY_X)
				func(D, mlx->key_release_param);
		}
		if (mlx->loop_hook)
		{
			(func)(void ) = (int (*)(void *))mlx->loop_hook;
			func(mlx->loop_param);
		}
		gfxFlushBuffers();
		gfxSwapBuffers();
		gspWaitForVBlank();
	}
	return (0);
}

int	mlx_hook(void *win_ptr, int x_event, int x_mask, int (*funct)(),
		void *param)
{
	extern void	*g_mlx_ptr;
	t_3ds_mlx	*mlx;

	(void)win_ptr;
	(void)x_mask;
	mlx = (t_3ds_mlx *)g_mlx_ptr;
	if (!mlx)
		return (0);
	if (x_event == 2)
	{ // ON_KEYDOWN
		mlx->key_press_hook = (void *)funct;
		mlx->key_press_param = param;
	}
	else if (x_event == 3)
	{ // ON_KEYUP
		mlx->key_release_hook = (void *)funct;
		mlx->key_release_param = param;
	}
	else if (x_event == 17)
	{ // ON_DESTROY
		mlx->destroy_hook = (void *)funct;
		mlx->destroy_param = param;
	}
	return (0);
}

int	mlx_loop_hook(void *mlx_ptr, int (*funct_ptr)(), void *param)
{
	t_3ds_mlx	*mlx;

	mlx = (t_3ds_mlx *)mlx_ptr;
	mlx->loop_hook = (int (*)(void *))funct_ptr;
	mlx->loop_param = param;
	return (0);
}

int	mlx_destroy_window(void *mlx_ptr, void *win_ptr)
{
	(void)mlx_ptr;
	(void)win_ptr;
	return (0);
}

int	mlx_destroy_image(void *mlx_ptr, void *img_ptr)
{
	t_3ds_img	*img;

	(void)mlx_ptr;
	img = (t_3ds_img *)img_ptr;
	if (img)
	{
		if (img->data)
			free(img->data);
		free(img);
	}
	return (0);
}

int	mlx_destroy_display(void *mlx_ptr)
{
	(void)mlx_ptr;
	return (0);
}

int	mlx_get_screen_size(void *mlx_ptr, int *sizex, int *sizey)
{
	(void)mlx_ptr;
	*sizex = SCREEN_WIDTH;
	*sizey = SCREEN_HEIGHT;
	return (0);
}

// VERY basic XPM loader for 3DS
static unsigned int	parse_xpm_color(char *s)
{
	if (s[0] == '#')
		return strtoul(s + 1, NULL, 16);
	if (!strcasecmp(s, "white"))
		return 0xFFFFFF;
	if (!strcasecmp(s, "black"))
		return 0x000000;
	if (!strcasecmp(s, "None"))
		return 0xFF00FF;
	return 0;
}

static char	*next_xpm_line(FILE *f, char *buf, int size)
{
	char	*p;

	while (fgets(buf, size, f))
	{
		p = strchr(buf, '"');
		if (p)
			return p;
	}
	return NULL;
}

void	*mlx_xpm_file_to_image(void *mlx_ptr, char *filename, int *width,
		int *height)
{
	char			buf[1024];
	FILE			*f;
	char			*p;
	unsigned int	*colors;
	char			**codes;
	char			*c_pos;
			char color_str[64];
	char			*start;
	char			*end;
	char			*space;
	t_3ds_img		*img;
	unsigned int	col;
	int				idx;

	snprintf(buf, sizeof(buf), "XPM: Loading %s...\n", filename);
	debug_log(buf);
	printf("XPM: Loading %s...\n", filename);
	f = fopen(filename, "r");
	if (!f)
	{
		snprintf(buf, sizeof(buf), "XPM: Error: Could not open %s\n", filename);
		debug_log(buf);
		printf("XPM: Error: Could not open %s\n", filename);
		return NULL;
	}
	p = next_xpm_line(f, buf, sizeof(buf));
	if (!p)
	{
		debug_log("XPM: Error: Could not find values line\n");
		fclose(f);
		return NULL;
	}
	int w, h, nc, cpp;
	if (sscanf(p + 1, "%d %d %d %d", &w, &h, &nc, &cpp) != 4)
	{
		debug_log("XPM: Error: Could not parse values line\n");
		fclose(f);
		return NULL;
	}
	snprintf(buf, sizeof(buf), "XPM: %dx%d, %d colors, %d cpp\n", w, h, nc,
		cpp);
	debug_log(buf);
	printf("XPM: %dx%d, %d colors, %d cpp\n", w, h, nc, cpp);
	*width = w;
	*height = h;
	colors = malloc(nc * sizeof(unsigned int));
	codes = malloc(nc * sizeof(char *));
	for (int i = 0; i < nc; i++)
	{
		p = next_xpm_line(f, buf, sizeof(buf));
		codes[i] = malloc(cpp + 1);
		strncpy(codes[i], p + 1, cpp);
		codes[i][cpp] = '\0';
		c_pos = strstr(p + 1 + cpp, "c ");
		if (c_pos)
		{
			start = c_pos + 2;
			end = strchr(start, '"');
			if (end)
				*end = '\0';
			strncpy(color_str, start, sizeof(color_str) - 1);
			color_str[sizeof(color_str) - 1] = '\0';
			space = strchr(color_str, ' ');
			if (space)
				*space = '\0';
			colors[i] = parse_xpm_color(color_str);
		}
		else
			colors[i] = 0;
	}
	img = mlx_new_image(mlx_ptr, w, h);
	for (int y = 0; y < h; y++)
	{
		p = next_xpm_line(f, buf, sizeof(buf));
		if (!p)
			break ;
		for (int x = 0; x < w; x++)
		{
			for (int i = 0; i < nc; i++)
			{
				if (!strncmp(p + 1 + x * cpp, codes[i], cpp))
				{
					col = colors[i];
					idx = (y * w + x) * 4;
					img->data[idx + 0] = (col >> 0) & 0xFF;
					img->data[idx + 1] = (col >> 8) & 0xFF;
					img->data[idx + 2] = (col >> 16) & 0xFF;
					img->data[idx + 3] = 0xFF;
					break ;
				}
			}
		}
	}
	for (int i = 0; i < nc; i++)
		free(codes[i]);
	free(codes);
	free(colors);
	fclose(f);
	debug_log("XPM: Loaded.\n");
	return img;
}

// Dummy implementations for others
int	mlx_mouse_hook(void *win_ptr, int (*funct_ptr)(), void *param)
{
	(void)win_ptr;
	(void)funct_ptr;
	(void)param;
	return 0;
}
int	mlx_key_hook(void *win_ptr, int (*funct_ptr)(), void *param)
{
	(void)win_ptr;
	(void)funct_ptr;
	(void)param;
	return 0;
}
int	mlx_expose_hook(void *win_ptr, int (*funct_ptr)(), void *param)
{
	(void)win_ptr;
	(void)funct_ptr;
	(void)param;
	return 0;
}
int	mlx_string_put(void *mlx_ptr, void *win_ptr, int x, int y, int color,
		char *string)
{
	(void)mlx_ptr;
	(void)win_ptr;
	(void)x;
	(void)y;
	(void)color;
	(void)string;
	return 0;
}
void	mlx_set_font(void *mlx_ptr, void *win_ptr, char *name)
{
	(void)mlx_ptr;
	(void)win_ptr;
	(void)name;
}
void	*mlx_xpm_to_image(void *mlx_ptr, char **xpm_data, int *width,
		int *height)
{
	(void)mlx_ptr;
	(void)xpm_data;
	(void)width;
	(void)height;
	return NULL;
}
int	mlx_mouse_get_pos(void *mlx_ptr, void *win_ptr, int *x, int *y)
{
	(void)mlx_ptr;
	(void)win_ptr;
	*x = 0;
	*y = 0;
	return 0;
}
int	mlx_mouse_move(void *mlx_ptr, void *win_ptr, int x, int y)
{
	(void)mlx_ptr;
	(void)win_ptr;
	(void)x;
	(void)y;
	return 0;
}
int	mlx_mouse_hide(void *mlx_ptr, void *win_ptr)
{
	(void)mlx_ptr;
	(void)win_ptr;
	return 0;
}
int	mlx_mouse_show(void *mlx_ptr, void *win_ptr)
{
	(void)mlx_ptr;
	(void)win_ptr;
	return 0;
}
