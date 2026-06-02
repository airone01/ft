
#include "fdf.h"

/**
 * @brief	Calculate the distance between two points
 *
 * @param	a	First point
 * @param	b	Second point
 *
 * @return	The distance between the two points
 */
double point_distance(t_point a, t_point b) {
  double dx;
  double dy;

  dx = b.x - a.x;
  dy = b.y - a.y;
  return (sqrt(dx * dx + dy * dy));
}
