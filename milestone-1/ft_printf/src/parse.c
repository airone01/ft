/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 17:15:51 by elagouch          #+#    #+#             */
/*   Updated: 2026/03/16 17:26:20 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

static void	init_format(t_format *fmt)
{
	fmt->minus = 0;
	fmt->zero = 0;
	fmt->hash = 0;
	fmt->space = 0;
	fmt->plus = 0;
	fmt->width = 0;
	fmt->precision = -1;
	fmt->type = 0;
}

static void	parse_flags(const char **fmt_str, t_format *fmt)
{
	while (**fmt_str == '-' || **fmt_str == '0' || **fmt_str == '#'
		|| **fmt_str == ' ' || **fmt_str == '+')
	{
		if (**fmt_str == '-')
			fmt->minus = 1;
		else if (**fmt_str == '0')
			fmt->zero = 1;
		else if (**fmt_str == '#')
			fmt->hash = 1;
		else if (**fmt_str == ' ')
			fmt->space = 1;
		else if (**fmt_str == '+')
			fmt->plus = 1;
		(*fmt_str)++;
	}
}

static void	parse_width_and_precision(const char **fmt_str, t_format *fmt)
{
	while (ft_isdigit(**fmt_str))
	{
		fmt->width = (fmt->width * 10) + (**fmt_str - '0');
		(*fmt_str)++;
	}
	if (**fmt_str == '.')
	{
		(*fmt_str)++;
		fmt->precision = 0;
		while (ft_isdigit(**fmt_str))
		{
			fmt->precision = (fmt->precision * 10) + (**fmt_str - '0');
			(*fmt_str)++;
		}
	}
}

/* Notes:
 * - We skip the initial '%' after the call to 'init_format()'
 * - Very last char we land on is the type specifier
 */
t_format	parse_format(const char **format)
{
	t_format	fmt;

	init_format(&fmt);
	(*format)++;
	parse_flags(format, &fmt);
	parse_width_and_precision(format, &fmt);
	fmt.type = **format;
	return (fmt);
}
