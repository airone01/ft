/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rush_putnbr_lang_extra.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@42>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 22:49:03 by elagouch          #+#    #+#             */
/*   Updated: 2024/09/29 23:31:04 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "h_main.h"

/*
 * Puts "special" numbers of a 3x.
 * "special" numbers are the ones between 11 and 19 included.
 */
void	putnbr_lang_3x_specials(struct s_lang_args args, int three_x)
{
	int	specials;

	specials = three_x % 100;
	if (args.ite != 0)
		ft_putstr(" ");
	ft_putstr(find_word(args.cube, args.len, specials, 0));
}

/*
 * Puts the `qty` ("thousand", "million", "billion", etc...).
 */
void	putnbr_lang_3x_qty(struct s_lang_args args, int three_x)
{
	(void) three_x;
	if (three_x > 0)
	{
		ft_putstr(" ");
		ft_putstr(find_word(args.cube, args.len, 1, args.qty));
	}
	args.ite++;
	args.qty--;
	if (get_3x(args) != 0)
		ft_putstr(" and");
}
