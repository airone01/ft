/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 13:56:34 by elagouch          #+#    #+#             */
/*   Updated: 2026/03/16 17:53:10 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <unistd.h>

static long	pf_display2(int fd, va_list *args, t_format *format)
{
	if (format->type == 'x' || format->type == 'X')
		return (print_hex(fd, format, va_arg(*args, unsigned int)));
	else if (format->type == '%')
		return (pfputchar(fd, '%'));
	return (0);
}

static long	pt_display(int fd, uintptr_t ptr)
{
	if (ptr == 0)
		return (pfputstr(fd, (char *)"(nil)"));
	return (pfputstr(fd, (char *)"0x") + pfputnbru_base(fd, ptr, BASE_16));
}

static long	pf_display(int fd, va_list *args, t_format *format)
{
	if (format->type == 'c')
		return (pfputchar(fd, (char)va_arg(*args, int)));
	else if (format->type == 's')
		return (print_string(fd, format, va_arg(*args, const char *)));
	else if (format->type == 'p')
		return (pt_display(fd, va_arg(*args, uintptr_t)));
	else if (format->type == 'd' || format->type == 'i')
		return (print_signed(fd, format, va_arg(*args, int)));
	else if (format->type == 'u')
		return (pfputnbru_base(fd, va_arg(*args, unsigned int), BASE_10));
	return (pf_display2(fd, args, format));
}

/*
 * @brief Formats and prints a string.
 *
 * @param format The formatting string
 * @param <...> The variables corresponding to the display calls introduced in
 * the formatting string
 *
 * @returns Upon success, the number of characters printed (excluding the
 * ending null byte).
 *
 * @see man printf.3
 */
int	ft_printf(const char *format, ...)
{
	va_list		args;
	long		count;
	t_format	fmt;

	count = 0;
	va_start(args, format);
	while (*format)
	{
		if (*format == '%')
		{
			fmt = parse_format(&format);
			count += pf_display(STDOUT_FILENO, &args, &fmt);
		}
		else
			count += pfputchar(STDOUT_FILENO, *format);
		if (*format)
			format++;
	}
	va_end(args);
	return ((int)count);
}

/*
 * @brief Formats and prints a string.
 *
 * @param format The formatting string
 * @param <...> The variables corresponding to the display calls introduced in
 * the formatting string
 *
 * @returns Upon success, the number of characters printed (excluding the
 * ending null byte).
 *
 * @see man printf.3
 */
int	ft_printf_fd(int fd, const char *format, ...)
{
	va_list		args;
	long		count;
	t_format	fmt;

	count = 0;
	va_start(args, format);
	while (*format)
	{
		if (*format == '%')
		{
			fmt = parse_format(&format);
			count += pf_display(STDOUT_FILENO, &args, &fmt);
		}
		else
			count += pfputchar(fd, *format);
		format++;
	}
	va_end(args);
	return ((int)count);
}
