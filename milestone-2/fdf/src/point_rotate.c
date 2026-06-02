
#include "fdf.h"

/**
 * @brief	Rotate a point around the origin by a given angle.
 *
 * @param	p		The point to rotate.
 * @param	angle	The angle to rotate the point by.
 *
 * @return	t_point	The rotated point.
 */
t_point point_rotate(t_point p, double angle) {
  t_point result;
  double cos_a;
  double sin_a;

  cos_a = cos(angle);
  sin_a = sin(angle);
  result.x = p.x * cos_a - p.y * sin_a;
  result.y = p.x * sin_a + p.y * cos_a;
  return (result);
}
