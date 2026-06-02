
#include "fdf.h"

/**
 * @brief	Calculate the magnitude of a point using the Pythagorean theorem
 *
 * @param	p		Point to calculate the magnitude
 *
 * @return	double	Magnitude of the point
 */
double point_magnitude(t_point p) { return (sqrt(p.x * p.x + p.y * p.y)); }
