/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 18:49:11 by elagouch          #+#    #+#             */
/*   Updated: 2025/02/05 22:21:43 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// GPM? begin ft_isalnum
/**
 * Tells if a character is alphanumerical (lowercase or uppercase or numerical
 * digit).
 *
 * @param	c	Character
 * @returns     Boolean result
 */
t_bool	ft_isalnum(char c)
{
	return (ft_isalpha(c) || ft_isdigit(c));
}
// GPM? end ft_isalnum
