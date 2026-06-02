
#include "fdf.h"

/**
 * @brief	Substracts two points
 *
 * @param	a	First point
 * @param	b	Second point
 *
 * @returns	t_point	Result of the substraction
 */
t_point point_sub(t_point a, t_point b) {
  t_point result;

  result.x = a.x - b.x;
  result.y = a.y - b.y;
  return (result);
}
