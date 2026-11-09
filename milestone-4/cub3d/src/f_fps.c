
#include "draw.h"
#include "mlx.h"
#include <stdio.h>
#include <sys/time.h>

/*
** Calculate time difference between two timeval structs in seconds
*/
static double get_time_diff(struct timeval *start, struct timeval *end) {
  return ((double)(end->tv_sec - start->tv_sec) +
          (double)(end->tv_usec - start->tv_usec) / 1000000.0);
}

void update_fps_counter(t_data *data) {
  double elapsed;

  gettimeofday(&data->current_frame, NULL);
  elapsed = get_time_diff(&data->last_frame, &data->current_frame);
  data->fps_timer += elapsed;
  data->frame_count++;
  if (data->fps_timer >= 0.5) {
    data->fps = data->frame_count / data->fps_timer;
    data->frame_count = 0;
    data->fps_timer = 0.0;
  }
}

void display_fps(t_data *data) {
  char fps_text[32];
  t_color c;

  int fps_counter_top = 0;
  int fps_counter_left = 0;
  c.val = 0x000000;
  snprintf(fps_text, sizeof(fps_text), "FPS: %.1f", data->fps);
  for (int y = fps_counter_top; y < fps_counter_top + FPS_COUNTER_TEXT_HEIGHT;
       y++) {
    for (int x = fps_counter_left;
         x < fps_counter_left + FPS_COUNTER_TEXT_WIDTH; x++) {
      if (x < data->win_width && y < data->win_height)
        my_mlx_pixel_put(&data->img, x, y, c);
    }
  }
  mlx_string_put(data->mlx, data->win, fps_counter_left * 2 + 5,
                 fps_counter_top * 2 + 15, 0xFFFFFF, fps_text);
}
