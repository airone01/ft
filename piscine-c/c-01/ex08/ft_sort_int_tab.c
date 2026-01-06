/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_int_tab.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <erwann.lagouche@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 17:44:33 by elagouch          #+#    #+#             */
/*   Updated: 2024/09/15 18:33:49 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <stdio.h>

void	ft_sort_int_tab(int *tab, int size)
{
	int	i;
	int	j;
	int	temp;

	i = 0;
	while (i < (size - 1))
	{
		j = 0;
		while (j < size - 1 - i)
		{
			if (tab[j] > tab[j + 1])
			{
				temp = tab[j + 1];
				tab[j + 1] = tab[j];
				tab[j] = temp;
			}
			j++;
		}
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
// 		src[i] = (i * 390) % 151;
// 		printf("[%d]: %d\n", i, src[i]);
// 		i++;
// 	}
// 	ft_sort_int_tab(src, 5);
// 	i = 0;
// 	while (i < size)
// 	{
// 		printf("[%d]: %d\n", i, src[i]);
// 		i++;
// 	}
// }
