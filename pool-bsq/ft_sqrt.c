/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sqrt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@42>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 16:53:46 by elagouch          #+#    #+#             */
/*   Updated: 2024/09/30 16:54:48 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
 * Gets the square root of a number.
 *
 * @param	nb	number
 *
 * @returns	square root
 * @returns	0 if no square root is found
 */
int	ft_sqrt(int nb)
{
	int	i;

	if (nb <= 1)
		return (0);
	i = 1;
	while ((i * i) < nb)
		i++;
	if ((i * i) == nb)
		return (i);
	return (0);
}
