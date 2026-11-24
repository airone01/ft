#include "sys_mouse.h"
#include "systems.h"

void sys_mouse_init(void) {
  game_system sys = get_sys(SYS_MOUSE);
  mouse_data dat = *((mouse_data *)sys.resources);

  dat.x = (int)(gamed.win_width * 0.5);
  dat.y = (int)(gamed.win_height * 0.5);
  dat.last_x = dat.x;
  dat.last_y = dat.y;
  dat.is_active = false;
  dat.first_move = true;
  dat.sensitivity = MOUSE_SENSITIVITY;
}

void mouse_toggle(void) {
  game_system sys = get_sys(SYS_MOUSE);
  mouse_data dat = *((mouse_data *)sys.resources);

  dat.is_active = !dat.is_active;
  if (dat.is_active)
    dat.first_move = true;
}

// void mouse_setup_hooks(t_data *data) {
//   mlx_hook(data->win, 6, 1L << 6, (t_hook)mouse_move_handler, data);
//   mlx_hook(data->win, 4, 1L << 2, (t_hook)mouse_press_handler, data);
// }