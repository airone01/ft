/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sqrt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@42>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 22:33:07 by elagouch          #+#    #+#             */
/*   Updated: 2024/09/22 23:05:27 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

// #include <stdio.h>
// #include <stdlib.h>
// #include <math.h>
// int	main(int argc, char **argv)
// {
// 	(void) argc;
// 	printf("%d", ft_sqrt(atoi(argv[1])));
// }
