
#include "fdf.h"

/**
 * @brief	Rotates a 3D point around the X axis.
 *
 * @param	p		The point to rotate.
 * @param	angle	The angle to rotate by.
 *
 * @returns	t_point3d	The rotated point.
 */
t_point3d rotate_x(t_point3d p, double angle) {
  t_point3d result;

  result.x = p.x;
  result.y = p.y * cos(angle) - p.z * sin(angle);
  result.z = p.y * sin(angle) + p.z * cos(angle);
  return (result);
}

/**
 * @brief	Rotates a 3D point around the Y axis.
 *
 * @param	p		The point to rotate.
 * @param	angle	The angle to rotate by.
 *
 * @returns	t_point3d	The rotated point.
 */
t_point3d rotate_y(t_point3d p, double angle) {
  t_point3d result;

  result.x = p.x * cos(angle) + p.z * sin(angle);
  result.y = p.y;
  result.z = -p.x * sin(angle) + p.z * cos(angle);
  return (result);
}

/**
 * @brief	Rotates a 3D point around the Z axis.
 *
 * @param	p		The point to rotate.
 * @param	angle	The angle to rotate by.
 *
 * @returns	t_point3d	The rotated point.
 */
t_point3d rotate_z(t_point3d p, double angle) {
  t_point3d result;

  result.x = p.x * cos(angle) - p.y * sin(angle);
  result.y = p.x * sin(angle) + p.y * cos(angle);
  result.z = p.z;
  return (result);
}
