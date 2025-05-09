/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 19:35:33 by elagouch          #+#    #+#             */
/*   Updated: 2025/05/08 16:56:41 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft.h"
# include <stdint.h>
# include <unistd.h>

long	ft_putnbr_base_ssize_ulong(int fd, uintptr_t nbr, char *base);
long	ft_putnbr_base_ssize_int(int fd, int nbr, char *base);
long	ft_putstr_ssize(int fd, char *str);
long	ft_putchar_ssize(int fd, char c);
int		ft_printf(const char *format, ...);
int		ft_printf_fd(int fd, const char *format, ...);

#endif
