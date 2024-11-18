/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_range.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@42>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 09:59:09 by elagouch          #+#    #+#             */
/*   Updated: 2024/09/24 10:38:24 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

/*
 * Returns:
 * - pointer to ints if everything worked
 * - NULL if malloc failed
 */
int	*ft_range(int min, int max)
{
	int	*dest;
	int	size;
	int	i;

	size = max - min;
	if (min >= max)
		return (0);
	dest = malloc(sizeof(int) * size);
	if (dest == 0)
		return (0);
	i = 0;
	while (i < size)
	{
		dest[i] = min;
		min++;
		i++;
	}
	return (dest);
}

// #include <stdio.h>
// int	main(int argc, char **argv)
// {
// 	int	*dest;
// 	int	i;
//
// 	if (argc != 3)
// 	{
// 		printf("Need 2 arguments.\n");
// 		return (1);
// 	}
// 	dest = ft_range(atoi(argv[1]), atoi(argv[2]));
// 	i = 0;
// 	while(i < atoi(argv[2]) - atoi(argv[1]))
// 	{
// 		printf("%d, ", dest[i]);
// 		i++;
// 	}
// 	free(dest);
// }
