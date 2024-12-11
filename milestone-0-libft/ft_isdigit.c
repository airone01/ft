/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 18:49:11 by elagouch          #+#    #+#             */
/*   Updated: 2024/12/11 18:23:17 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * Tells if a character is a decimal digit
 * @param	c	Character
 * @returns     Boolean result
 */
int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}
