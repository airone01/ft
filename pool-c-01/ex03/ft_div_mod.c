/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_div_mod.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <erwann.lagouche@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 08:07:17 by elagouch          #+#    #+#             */
/*   Updated: 2024/09/12 08:13:50 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <stdio.h>

void	ft_div_mod(int a, int b, int *div, int *mod)
{
	int	res_div;
	int	res_mod;

	res_div = a / b;
	res_mod = a % b;
	*div = res_div;
	*mod = res_mod;
}

// int	main(void)
// {
// 	int	a;
// 	int	b;
// 	int	div;
// 	int	mod;
//
// 	a = 420;
// 	b = 69;
// 	div = 0;
// 	mod = 0;
// 	printf("a: %d, b: %d, div: %d, mod: %d\n", a, b, div, mod);
//
// 	ft_div_mod (a, b, &div, &mod);
//
// 	printf("a: %d, b: %d, div: %d, mod: %d\n", a, b, div, mod);
// }
