
#include "fdf.h"

/**
 * @brief	Calculate the dot product of two points
 *
 * @param	a	First point
 * @param	b	Second point
 *
 * @return	double	The dot product of the two points
 */
double point_dot(t_point a, t_point b) { return (a.x * b.x + a.y * b.y); }
