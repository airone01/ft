/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_iterative_factorial.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@42>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 08:52:37 by elagouch          #+#    #+#             */
/*   Updated: 2024/09/21 08:59:06 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_iterative_factorial(int nb)
{
	int	i;
	int	count;

	if (nb < 0)
		return (0);
	i = 1;
	count = 1;
	while (i <= nb)
	{
		count *= i;
		i++;
	}
	return (count);
}

// #include <stdio.h>
// #include <stdlib.h>
// int	main(int argc, char **argv)
// {
// 	(void) argc;
// 	printf("%d", ft_iterative_factorial(atoi(argv[1])));
// }
