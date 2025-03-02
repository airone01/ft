/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 18:49:11 by elagouch          #+#    #+#             */
/*   Updated: 2025/01/14 20:26:41 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// GPM? begin ft_tolower
/**
 * If c is an uppercase letter, tolower() returns its lowercase equivalent,  if
 * a  lowercase representation exists in the current locale.  Otherwise, it re‐
 * turns c.  The tolower_l() function performs the same task, but uses the  lo‐
 * cale referred to by the locale handle locale.
 * @param	c	Character
 * @returns     Uppercase character or c i the conversion was not possible
 */
int	ft_tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
		return (c + 32);
	return (c);
}
// GPM? end ft_tolower
