/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_signed.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 17:48:37 by elagouch          #+#    #+#             */
/*   Updated: 2026/03/16 18:37:41 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	get_num_len(long nbr)
{
	int	len;

	len = 0;
	if (nbr == 0)
		return (1);
	if (nbr < 0)
	{
		len++;
		nbr = -nbr;
	}
	while (nbr > 0)
	{
		len++;
		nbr /= 10;
	}
	return (len);
}

/* util function to calc padding (and avoid the norm) */
static void	calc_pad(t_format *fmt, int nbr, int *pad)
{
	int	sign_len;

	pad[2] = get_num_len(nbr) - (nbr < 0);
	if (nbr == 0 && fmt->precision == 0)
		pad[2] = 0;
	sign_len = (nbr < 0) || fmt->plus || fmt->space;
	pad[0] = 0;
	if (fmt->precision > pad[2])
		pad[0] = fmt->precision - pad[2];
	else if (fmt->zero && fmt->precision == -1 && !fmt->minus)
		pad[0] = fmt->width - pad[2] - sign_len;
	if (pad[0] < 0)
		pad[0] = 0;
	pad[1] = fmt->width - (pad[2] + pad[0] + sign_len);
	if (pad[1] < 0)
		pad[1] = 0;
}

/* pad[0]=zeros, pad[1]=spaces, pad[2]=digits */
long	print_signed(int fd, t_format *fmt, int nbr)
{
	long			count;
	unsigned int	unbr;
	int				pad[3];

	count = 0;
	if (nbr < 0)
		unbr = -(unsigned int)nbr;
	else
		unbr = (unsigned int)nbr;
	calc_pad(fmt, nbr, pad);
	if (!fmt->minus)
		count += print_padding(fd, 0, pad[1], ' ');
	if (nbr < 0)
		count += pfputchar(fd, '-');
	else if (fmt->plus)
		count += pfputchar(fd, '+');
	else if (fmt->space)
		count += pfputchar(fd, ' ');
	count += print_padding(fd, 0, pad[0], '0');
	if (pad[2] > 0)
		count += pfputnbru_base(fd, unbr, BASE_10);
	if (fmt->minus)
		count += print_padding(fd, 0, pad[1], ' ');
	return (count);
}
