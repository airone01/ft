/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_feq.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 14:56:47 by elagouch          #+#    #+#             */
/*   Updated: 2025/06/23 13:51:09 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// GPM? begin ft_feq
bool	ft_feq(double a, double b)
{
	double	diff;
	double	scale;

	diff = ft_fabs(a - b);
	if (diff < DBL_EPSILON)
		return (true);
	scale = ft_fmax(ft_fabs(a), ft_fabs(b));
	return (diff < DBL_EPSILON * (1.0 + scale));
}
// GPM? end ft_feq
