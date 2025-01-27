/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 18:49:11 by elagouch          #+#    #+#             */
/*   Updated: 2025/01/14 20:18:05 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// GPM? begin ft_isdigit
/**
 * Tells if a character is a decimal digit
 * @param	c	Character
 * @returns     Boolean result
 */
int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}
// GPM? end ft_isdigit
