#ifndef PAL_H
#define PAL_H

#include <cub3d.h>
#include <game.h>

/*
** Info for the MLX stored here for convenience
*/
typedef struct {
  void *img;
  unsigned int *addr;
  int bits_per_pixel;
  int line_length;
  int endian;
} img;

typedef struct {
  /// The platform general data.
  /// Ex what is returned by 'mlx_init()'.
  void *dat;
  /// The window object of the platform.
  void *win;
  /// The image to put pixels to
  img img;
} pal_data;

extern pal_data pal;

// Initialize system resources.
// @return 0 on success.
// @return 1 on error. Should free and close then.
int pal_init(void);
// Free system resources
void pal_free(void);

void pixel_put(img *img, vec2 coords, color color);

#endif /* PAL_H */