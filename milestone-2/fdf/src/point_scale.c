
#include "fdf.h"

/**
 * @brief	Scales a point
 *
 * @param	p		Point to scale
 * @param	scale	Scale factor
 *
 * @returns	t_point	Result of the scaling
 */
t_point point_scale(t_point p, double scale) {
  t_point result;

  result.x = p.x * scale;
  result.y = p.y * scale;
  return (result);
}
