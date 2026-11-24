#include "mlx.h"
#include <cub3d.h>
#include <pal.h>
#include <pal_mlx.h>
#include <stdbool.h>
#include <stdio.h>

pal_data pal = {.dat = NULL, .win = NULL, .img = {NULL, NULL, -1, -1, -1}};

int pal_init(void) {
  pal.dat = mlx_init();
  if (!pal.dat)
    return 1;
  pal.win = mlx_new_window(pal.dat, gamed.win_width, gamed.win_height,
                           (char *)"~~~ kyubu kui ~~~");
  if (!pal.data)
    return 1;
  pal.img = mlx_new_image(pal.dat, game.win_width, game.win_height);
  pal.img.addr = mlx_get_data_addr(&pal.img.img, &pal.img.bits_per_pixel,
                                   &pal.img.line_length, &pal.img.endian);
  return 0;
}

void pixel_put(img *img, vec2 coords, color color) {
  unsigned int *dst;

  if (!img || !img->addr)
    return;
  if (coords.x < 0 || coords.y < 0 || coords.x >= gamed.win_width ||
      coords.y >= gamed.win_height)
    return;
  dst = img->addr +
        (coords.y * img->line_length + coords.x * (img->bits_per_pixel / 8));
  *dst = color.val;
}

void pal_free(void) {
  if (pal.img.img)
    mlx_destroy_image(pal.dat, pal.img.img);
  if (pal.win)
    mlx_destroy_window(pal.dat, pal.win);
  if (pal.dat) {
    mlx_destroy_display(pal.dat);
    free(pal.dat);
  }
}