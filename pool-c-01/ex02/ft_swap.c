/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_swap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <erwann.lagouche@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 07:51:11 by elagouch          #+#    #+#             */
/*   Updated: 2024/09/12 08:03:13 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <stdio.h>

void	ft_swap(int *a, int *b)
{
	int	val_a;
	int	val_b;

	val_a = *a;
	val_b = *b;
	*a = val_b;
	*b = val_a;
}

// int	main(void)
// {
// 	int a;
// 	int b;
//
// 	a = 69;
// 	b = 420;
// 	printf("a: %d, b: %d\n", a, b);
//
// 	ft_swap (&a, &b);
// 	printf("a: %d, b: %d", a, b);
// }
