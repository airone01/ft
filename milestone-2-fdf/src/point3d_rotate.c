/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point3d_rotate.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 20:18:56 by elagouch          #+#    #+#             */
/*   Updated: 2025/02/21 20:19:05 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_point3d	rotate_x(t_point3d p, double angle)
{
	t_point3d	result;

	result.x = p.x;
	result.y = p.y * cos(angle) - p.z * sin(angle);
	result.z = p.y * sin(angle) + p.z * cos(angle);
	return (result);
}

t_point3d	rotate_y(t_point3d p, double angle)
{
	t_point3d	result;

	result.x = p.x * cos(angle) + p.z * sin(angle);
	result.y = p.y;
	result.z = -p.x * sin(angle) + p.z * cos(angle);
	return (result);
}

t_point3d	rotate_z(t_point3d p, double angle)
{
	t_point3d	result;

	result.x = p.x * cos(angle) - p.y * sin(angle);
	result.y = p.x * sin(angle) + p.y * cos(angle);
	result.z = p.z;
	return (result);
}
