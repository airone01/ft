/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 18:49:11 by elagouch          #+#    #+#             */
/*   Updated: 2025/01/05 01:29:56 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// GPM? begin ft_strlen
/**
 * Gets the length of a string.
 * @param	str	String to get length from
 * @retuns      Length of str
 */
size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}
// GPM? end ft_strlen
