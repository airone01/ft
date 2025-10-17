/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ultimate_div_mod.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <erwann.lagouche@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 08:14:57 by elagouch          #+#    #+#             */
/*   Updated: 2024/09/12 08:23:59 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <stdio.h>

void	ft_ultimate_div_mod(int *a, int *b)
{
	int	x;
	int	y;

	x = *a / *b;
	y = *a % *b;
	*a = x;
	*b = y;
}

// int	main(void)
// {
// 	int	a;
// 	int	b;
//
// 	a = 420;
// 	b = 69;
// 	printf ("a: %d, b: %d\n", a, b);
// 	ft_ultimate_div_mod (&a, &b);
// 	printf ("a: %d, b: %d\n", a, b);
// }
