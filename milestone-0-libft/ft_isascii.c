/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 16:00:00 by elagouch          #+#    #+#             */
/*   Updated: 2025/01/14 20:17:49 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// GPM? begin ft_isascii
/*
 * Tells if a character is in the ASCII tabe
 *
 * @param	c	character
 *
 * @returns	boolean result
 */
int	ft_isascii(int c)
{
	return (c <= 127 && c >= 0);
}
// GPM? end ft_isascii
