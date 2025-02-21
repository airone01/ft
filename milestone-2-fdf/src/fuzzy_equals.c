/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fuzzy_equals.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 14:56:47 by elagouch          #+#    #+#             */
/*   Updated: 2025/02/21 10:31:56 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/**
 * 	Comparing floats with == or != is dangerous because of floating point
 *	precision. This function checks if two floats are equal within a certain
 *	epsilon range.
 *
 *	@see	https://stackoverflow.com/a/32334103
 */
t_bool	fuzzy_equals(double a, double b)
{
	double	diff;
	double	scale;

	diff = fabs(a - b);
	if (diff < DBL_EPSILON)
		return (true);
	scale = fmax(fabs(a), fabs(b));
	return (diff < DBL_EPSILON * (1.0 + scale));
}
