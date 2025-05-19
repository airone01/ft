/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_recursive_power.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@42>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 09:42:28 by elagouch          #+#    #+#             */
/*   Updated: 2024/09/21 09:42:33 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_recursive_power(int nb, int power)
{
	if (power < 0)
		return (0);
	if (power == 0)
		return (1);
	return (ft_recursive_power(nb, power - 1) * nb);
}

// #include <stdio.h>
// #include <stdlib.h>
// # include <math.h>
// int	main(int argc, char **argv)
// {
// 	(void) argc;
// 	// printf("%d\n\n", pow(100, 0));
// 	printf("%d", ft_recursive_power(atoi(argv[1]), atoi(argv[2])));
// }
