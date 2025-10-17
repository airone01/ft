/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rush_putnbr_lang_qty.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@42>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 22:44:50 by elagouch          #+#    #+#             */
/*   Updated: 2024/09/29 23:30:48 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "h_main.h"

/*
 * Puts the hundreds of a 3x
 */
void	putnbr_lang_3x_hundreds(struct s_lang_args args, int three_x)
{
	int	hundreds;

	hundreds = three_x / 100;
	if (hundreds <= 0)
		return ;
	if (args.ite != 0)
		ft_putstr(" ");
	ft_putstr(find_word(args.cube, args.len, hundreds, 0));
	ft_putstr(" hundred");
}

/*
 * Puts the tens of a 3x
 */
void	putnbr_lang_3x_tens(struct s_lang_args args, int three_x)
{
	int	tens;

	tens = (three_x / 10) % 10;
	if (tens <= 0)
		return ;
	if (three_x / 100 > 0)
		ft_putstr(" ");
	ft_putstr(find_word(args.cube, args.len, tens * 10, 0));
}

/*
 * Puts the units of a 3x
 */
void	putnbr_lang_3x_units(struct s_lang_args args, int three_x)
{
	int	units;

	units = three_x % 10;
	if (units <= 0)
		return ;
	if ((three_x / 10) % 10 > 0)
		ft_putstr("-");
	else if (args.ite != 0)
		ft_putstr(" ");
	ft_putstr(find_word(args.cube, args.len, units, 0));
}
