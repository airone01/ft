
#include "mouse_bonus.h"

void handle_scroll_wheel(int button) {
  t_mouse *mouse;

  mouse = mouse_get_state();
  if (button == MOUSE_SCROLL_UP) {
    if (mouse->sensitivity < MOUSE_MAX)
      mouse->sensitivity += 0.0005;
  }
  if (button == MOUSE_SCROLL_DOWN) {
    if (mouse->sensitivity > MOUSE_MIN)
      mouse->sensitivity -= 0.0005;
  }
}

int mouse_press_handler(int button) {
  if (button == MOUSE_LEFT_CLICK)
    mouse_toggle();
  if (button == MOUSE_SCROLL_UP || button == MOUSE_SCROLL_DOWN)
    handle_scroll_wheel(button);
  return (0);
}
