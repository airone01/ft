/* ************************************************************************** */
/*                                                                            */
/*                                                     _    ⣀⣀⣀⡀⡀⡀⡀⣀⡀⣀⣀⣀⡀  */
/*   ft_printf.c                                   _ _/ |   ⡇⣶⡆⡇⡾⢏⡭⡵⠀⡇⣶⡆⡇  */
/*                                                | '_| |_  ⣓⣒⠒⡃⡂⣏⡆⡯⢇⠓⠶⠖⡃  */
/*   By: elagouch <elagouch@student.42.fr>        |_|_|_(@) ⢻⣊⡞⣪⢳⡗⣳⢤⣈⢍⣰⢖⡇  */
/*                                                | | |_  ) ⠜⡲⡢⣲⡯⡼⡑⡁⣝⣘⡚⢠⠅  */
/*   Created: 2024/11/19 13:56:34 by elagouch     |_  _/ /  ⡖⣒⡒⡆⠉⠧⢰⣮⣇⣂⡏⡳⡆  */
/*   Updated: 2024/11/19 14:00:17 by elagouch       |_/___| ⣇⣛⣃⡇⡿⢤⠤⠾⠡⠹⢝⣚⡁  */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"
#include <stdarg.h>
#include <stddef.h>
#include <unistd.h>

static ssize_t	pf_display2(va_list *args, const char *format)
{
	if (*format == 'x')
		return (ft_putnbr_base_ssize(va_arg(*args, unsigned int),
				"0123456789abcdef"));
	else if (*format == 'X')
		return (ft_putnbr_base_ssize(va_arg(*args, unsigned int),
				"0123456789ABCDEF"));
	else if (*format == '%')
		return (ft_putchar_ssize('%'));
	return (0);
}

static ssize_t	pt_display(size_t ptr)
{
	if (ptr == 0)
		return (ft_putstr_ssize("(nil)"));
	return (ft_putstr_ssize("0x") + ft_putnbr_base_ssize(ptr,
			"0123456789abcdef"));
}

static ssize_t	pf_display(va_list *args, const char *format)
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
		return (pt_display(va_arg(*args, size_t)));
	else if (*format == 'd' || *format == 'i')
		return (ft_putnbr_base_ssize(va_arg(*args, int), "0123456789"));
	else if (*format == 'u')
		return (ft_putnbr_base_ssize(va_arg(*args, unsigned int),
				"0123456789"));
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
	size_t	count;

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
	return (count);
}
