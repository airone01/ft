/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 18:49:11 by elagouch          #+#    #+#             */
/*   Updated: 2025/02/05 23:03:01 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// GPM? begin ft_striteri
/**
 * Applies the function ’f’ on each character of the string passed as argument,
 * passing its index as first argument. Each character is passed by address to
 * ’f’ to be modified if necessary.
 * @param	s	The string on which to iterate
 * @param	f	The function to apply to each character
 */
void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	unsigned int	i;

	i = 0;
	while (*s)
		f(i++, s++);
}
// GPM? end ft_striteri
