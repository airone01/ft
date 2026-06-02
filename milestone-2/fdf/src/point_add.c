
#include "fdf.h"

/**
 * @brief	Adds two points
 *
 * @param	a	First point
 * @param	b	Second point
 *
 * @returns	t_point	Result of the addition
 */
t_point point_add(t_point a, t_point b) {
  t_point result;

  result.x = a.x + b.x;
  result.y = a.y + b.y;
  return (result);
}
