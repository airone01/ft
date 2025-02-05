/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isspace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 22:11:30 by elagouch          #+#    #+#             */
/*   Updated: 2025/02/05 22:12:53 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Checks if a character is a space.
 *
 * @param	c	Character to check
 *
 * @returns		True if the character is a space
 * @returns		False otherwise
 */
t_bool	ft_isspace(char c)
{
	return (c == ' ' || (c >= '\t' && c <= '\r'));
}
