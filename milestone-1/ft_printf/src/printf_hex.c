/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_hex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 17:49:28 by elagouch          #+#    #+#             */
/*   Updated: 2026/03/16 18:37:54 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	get_hex_len(unsigned int nbr)
{
	int	len;

	len = 0;
	if (nbr == 0)
		return (1);
	while (nbr > 0)
	{
		len++;
		nbr /= 16;
	}
	return (len);
}

/* util function to calc padding (and avoid the norm) */
static void	calc_hex_pad(t_format *fmt, unsigned int nbr, int *pad)
{
	int	hash_len;

	hash_len = 0;
	pad[2] = get_hex_len(nbr);
	if (nbr == 0 && fmt->precision == 0)
		pad[2] = 0;
	if (fmt->hash && nbr != 0)
		hash_len = 2;
	pad[0] = 0;
	if (fmt->precision > pad[2])
		pad[0] = fmt->precision - pad[2];
	else if (fmt->zero && fmt->precision == -1 && !fmt->minus)
		pad[0] = fmt->width - pad[2] - hash_len;
	if (pad[0] < 0)
		pad[0] = 0;
	pad[1] = fmt->width - (pad[2] + pad[0] + hash_len);
	if (pad[1] < 0)
		pad[1] = 0;
}

/* pad[0]=zeros, pad[1]=spaces, pad[2]=digits */
long	print_hex(int fd, t_format *fmt, unsigned int nbr)
{
	long	count;
	int		pad[3];

	count = 0;
	calc_hex_pad(fmt, nbr, pad);
	if (!fmt->minus)
		count += print_padding(fd, 0, pad[1], ' ');
	if (fmt->hash && nbr != 0)
	{
		if (fmt->type == 'x')
			count += pfputstr(fd, "0x");
		else
			count += pfputstr(fd, "0X");
	}
	count += print_padding(fd, 0, pad[0], '0');
	if (pad[2] > 0)
	{
		if (fmt->type == 'x')
			count += pfputnbru_base(fd, nbr, BASE_16);
		else
			count += pfputnbru_base(fd, nbr, BASE_16C);
	}
	if (fmt->minus)
		count += print_padding(fd, 0, pad[1], ' ');
	return (count);
}
