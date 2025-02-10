/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 13:56:34 by elagouch          #+#    #+#             */
/*   Updated: 2025/02/10 19:23:18 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdarg.h>
#include <stddef.h>
#include <unistd.h>

static long	pf_display2(va_list *args, const char *format)
{
	if (*format == 'x')
		return (ft_putnbr_base_ssize_ulong(va_arg(*args, unsigned int),
				(char *)"0123456789abcdef"));
	else if (*format == 'X')
		return (ft_putnbr_base_ssize_ulong(va_arg(*args, unsigned int),
				(char *)"0123456789ABCDEF"));
	else if (*format == '%')
		return (ft_putchar_ssize('%'));
	return (0);
}

static long	pt_display(uintptr_t ptr)
{
	if (ptr == 0)
		return (ft_putstr_ssize((char *)"(nil)"));
	return (ft_putstr_ssize((char *)"0x") + ft_putnbr_base_ssize_ulong(ptr,
			(char *)"0123456789abcdef"));
}

static long	pf_display(va_list *args, const char *format)
{
	void	*tmp;

	tmp = 0;
	if (*format == 'c')
		return (ft_putchar_ssize((char)va_arg(*args, int)));
	else if (*format == 's')
	{
		tmp = va_arg(*args, char *);
		return (ft_putstr_ssize(tmp));
	}
	else if (*format == 'p')
		return (pt_display(va_arg(*args, uintptr_t)));
	else if (*format == 'd' || *format == 'i')
		return (ft_putnbr_base_ssize_int(va_arg(*args, int),
				(char *)"0123456789"));
	else if (*format == 'u')
		return (ft_putnbr_base_ssize_ulong(va_arg(*args, unsigned int),
				(char *)"0123456789"));
	return (pf_display2(args, format));
}

/*
 * Format and print a string.
 * @see		man printf.3
 *
 * @param	format	the formatting string
 * @param	...		tyhe rest of the variables of types introduces in format
 *
 * @returns	Upon  successful return, these functions return the number of
 *								characters printed (excluding the
 *			null byte used to end output to strings).
 */
int	ft_printf(const char *format, ...)
{
	va_list	args;
	long	count;

	count = 0;
	va_start(args, format);
	while (*format)
	{
		if (*format == '%')
			count += pf_display(&args, ++format);
		else
			count += ft_putchar_ssize(*format);
		format++;
	}
	va_end(args);
	return ((int)count);
}
