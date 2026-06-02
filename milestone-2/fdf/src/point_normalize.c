
#include "fdf.h"

/**
 * @brief	Normalize a point
 *
 * @param	p	Point to normalize
 *
 * @returns	t_point	Normalized point
 */
t_point point_normalize(t_point p) {
  double mag;

  mag = point_magnitude(p);
  if (ft_feq(mag, 0.0))
    return (p);
  return (point_scale(p, 1.0 / mag));
}
