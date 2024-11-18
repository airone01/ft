/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rev_int_tab.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <erwann.lagouche@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 17:44:33 by elagouch          #+#    #+#             */
/*   Updated: 2024/09/15 18:04:52 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <stdio.h>

void	ft_rev_int_tab(int *tab, int size)
{
	int	dest[500];
	int	i;

	i = 0;
	while (i <= size)
	{
		dest[i] = tab[i];
		i++;
	}
	i = 0;
	while (i <= size)
	{
		tab[i] = dest[size - i - 1];
		i++;
	}
}

// int	main(void)
// {
// 	const int	size = 5;
// 	int			i;
// 	int			src[size];
//
// 	i = 0;
// 	while (i < size)
// 	{
// 		src[i] = i;
// 		printf("[%d]: %d\n", i, src[i]);
// 		i++;
// 	}
// 	ft_rev_int_tab(src, 5);
// 	i = 0;
// 	while (i < size)
// 	{
// 		printf("[%d]: %d\n", i, src[i]);
// 		i++;
// 	}
// }
