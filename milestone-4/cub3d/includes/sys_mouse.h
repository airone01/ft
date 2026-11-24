#ifndef SYS_MOUSE_H
#define SYS_MOUSE_H

#include "cub3d.h"

#define SYS_MOUSE "CUB_MOUSE"

/*******************************************************************************
 *                                    Macros                                   *
 ******************************************************************************/

#define MOUSE_SENSITIVITY 0.001
#define MOUSE_MIN 0.0005
#define MOUSE_MAX 0.005
#define MOUSE_LEFT_CLICK 1
#define MOUSE_RIGHT_CLICK 3
#define MOUSE_SCROLL_UP 4
#define MOUSE_SCROLL_DOWN 5

/*******************************************************************************
 *                                  Structures                                 *
 ******************************************************************************/

typedef struct {
  int x;
  int y;
  int last_x;
  int last_y;
  bool is_active;
  bool first_move;
  double sensitivity;
} mouse_data;

/*******************************************************************************
 *                             Function Prototypes                             *
 ******************************************************************************/

/**
 * @brief Handle mouse scroll wheel events
 *
 * @param button Mouse button code (MOUSE_SCROLL_UP/DOWN)
 */
void handle_scroll_wheel(int button);

/**
 * @brief Process mouse button press events
 *
 * @param button Mouse button identifier
 * @return 0 on success
 */
int mouse_press_handler(int button);

/**
 * Toggle mouse activation state
 */
void mouse_toggle(void);

/**
 * @brief Setup MLX mouse event hooks
 *
 * @param data Main game data structure
 */
void mouse_setup_hooks(t_data *data);

/**
 * @brief Handle mouse movement events and camera rotation
 *
 * @param x Current mouse X coordinate
 * @param y Current mouse Y coordinate
 * @param data Main game data structure
 * @return 0 on success
 */
int mouse_move_handler(int x, int y, t_data *data);

#endif /* SYS_MOUSE_H */