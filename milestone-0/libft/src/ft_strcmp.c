/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 16:27:23 by elagouch          #+#    #+#             */
/*   Updated: 2025/05/12 01:30:29 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <limits.h>

// GPM? begin ft_strcmp
int	ft_strcmp(const char *s1, const char *s2)
{
	return (ft_strncmp(s1, s2, ULLONG_MAX));
}
// GPM? end ft_strcmp
