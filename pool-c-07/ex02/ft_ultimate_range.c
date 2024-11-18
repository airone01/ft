/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ultimate_range.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@42>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 10:33:06 by elagouch          #+#    #+#             */
/*   Updated: 2024/09/24 11:58:44 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

/*
 * Populates an array of ints with ints between `min` and `max`.
 *
 * `range` will be:
 * - the array of ints
 * - if failed, undefined
 * - if bad values, 0
 *
 * Returns:
 * - the size of the array of ints
 * - if failed, -1
 * - if bad values, 0
 */
int	ft_ultimate_range(int **range, int min, int max)
{
	int	i;
	int	*tab;
	int	size;

	size = max - min;
	tab = malloc(sizeof(*tab) * (size));
	if (min >= max)
	{
		*range = NULL;
		return (0);
	}
	if (tab == NULL)
	{
		*range = NULL;
		return (-1);
	}
	i = 0;
	while (min < max)
	{
		tab[i] = min;
		i++;
		min++;
	}
	*range = tab;
	return (size);
}

// #include <stdio.h>
// int	main(int argc, char **argv)
// {
// 	int	*range;
// 	int	res;
// 	int	i;
// 	int	min;
// 	int	max;
//
// 	if (argc < 3)
// 	{
// 		printf("Too few args");
// 		return (1);
// 	}
// 	min = atoi(argv[1]);
// 	max = atoi(argv[2]);
// 	range = 0;
// 	res = ft_ultimate_range(&range, min, max);
// 	if (res <= 0)
// 	{
// 		printf("Erreur: %d\n", res);
// 		return (1);
// 	}
// 	i = 0;
// 	while(i < max - min)
// 	{
// 		printf("%d ", range[i]);
// 		i++;
// 	}
//
// 	free(range);
// }
