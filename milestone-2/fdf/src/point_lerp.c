
#include "fdf.h"

/**
 * @brief	Linear interpolation between two points
 *
 * @param	a	First point
 * @param	b	Second point
 * @param	t	Interpolation factor
 *
 * @return	t_point	Interpolated point
 */
t_point point_lerp(t_point a, t_point b, double t) {
  t_point result;

  result.x = a.x + (b.x - a.x) * t;
  result.y = a.y + (b.y - a.y) * t;
  return (result);
}
