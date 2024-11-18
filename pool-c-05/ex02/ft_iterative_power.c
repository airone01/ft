/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_iterative_power.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@42>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 09:15:07 by elagouch          #+#    #+#             */
/*   Updated: 2024/09/21 09:39:19 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_iterative_power(int nb, int power)
{
	int	i;
	int	init;

	if (power < 0)
		return (0);
	if (power == 0)
		return (1);
	i = 1;
	init = nb;
	while (i < power)
	{
		nb *= init;
		i++;
	}
	return (nb);
}

// #include <stdio.h>
// #include <stdlib.h>
// # include <math.h>
// int	main(int argc, char **argv)
// {
// 	(void) argc;
// 	// printf("%d\n\n", pow(100, 0));
// 	printf("%d", ft_iterative_power(atoi(argv[1]), atoi(argv[2])));
// }
