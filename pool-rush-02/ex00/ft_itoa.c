/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 16:41:30 by gaducurt          #+#    #+#             */
/*   Updated: 2024/11/19 12:15:13 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "h_main.h"

static int	count_size(int n)
{
	int	i;

	i = 0;
	if (n < 0)
		n *= -1;
	while (n != 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

// /*
//  * Basic implementation of itoa.
//  * Uses ft_strnew to allocate a new string.
//  */
// char	*ft_itoa(int nb)
// {
// 	char	*dest;
// 	int		count;
// 	int		n;
// 	int		i;

// 	n = nb;
// 	count = count_size(n);
// 	i = 0;
// 	if (n < 0 || count == 0)
// 		count++;
// 	if (!(dest = ft_strnew(count + 1)))
// 		return (NULL);
// 	if (n < 0)
// 	{
// 		n *= -1;
// 		dest[0] = '-';
// 		i++;
// 	}
// 	while (count > i)
// 	{
// 		count--;
// 		dest[count] = (n % 10) + '0';
// 		n /= 10;
// 	}
// 	return (dest);
// }
