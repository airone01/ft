#include "cub3d.h"
#include "draw.h"
#include "mlx.h"
#include "mlx_hook.h"
#include "player.h"

void handle_mlx_bonus_features(t_data *data, int keycode) {
  (void)data;
  (void)keycode;
}

void setup_mlx_hooks(t_data *data) {
  mlx_loop_hook(data->mlx, (t_hook)render_frame, data);
  mlx_hook(data->win, ON_DESTROY, 0, (t_hook)hook_destroy, data);
  mlx_hook(data->win, ON_KEYDOWN, 1L << 0, (t_hook)key_press, data);
  mlx_hook(data->win, ON_KEYUP, 1L << 1, (t_hook)key_release, data);
}
