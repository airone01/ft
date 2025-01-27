/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 18:49:11 by elagouch          #+#    #+#             */
/*   Updated: 2025/01/14 20:26:56 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// GPM? begin ft_toupper
/**
 * If  c  is a lowercase letter, toupper() returns its uppercase equivalent, if
 * an uppercase representation exists in the current locale.  Otherwise, it re‐
 * turns  c.  The toupper_l() function performs the same task, but uses the lo‐
 * cale referred to by the locale handle locale.
 * @param	c	Character
 * @returns     Uppercase character or c i fthe conversion was not possible
 */
int	ft_toupper(int c)
{
	if (c >= 'a' && c <= 'z')
		return (c - 32);
	return (c);
}
// GPM? end ft_toupper
