/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sqrt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 22:33:07 by elagouch          #+#    #+#             */
/*   Updated: 2025/01/02 22:34:49 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_sqrt(int nb)
{
	int	i;

	if (nb < 1)
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
