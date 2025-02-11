/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 19:35:33 by elagouch          #+#    #+#             */
/*   Updated: 2025/02/10 19:39:50 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "../milestone-0-libft/libft.h"                 // GPM!

# include <stdint.h>
# include <unistd.h>

long	ft_putnbr_base_ssize_ulong(uintptr_t nbr, char *base);
long	ft_putnbr_base_ssize_int(int nbr, char *base);
long	ft_putstr_ssize(char *str);
long	ft_putchar_ssize(char c);
int		ft_printf(const char *format, ...);

#endif
