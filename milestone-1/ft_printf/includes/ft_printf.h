/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 19:35:33 by elagouch          #+#    #+#             */
/*   Updated: 2026/03/16 14:39:43 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
#define FT_PRINTF_H

#include "libft.h"
#include <stdint.h>
#include <unistd.h>

#ifndef BASE_10
#define BASE_10 "0123456789"
#endif /* ifndef BASE_10 */

#ifndef BASE_16
#define BASE_16 "0123456789abcdef"
#endif /* ifndef BASE_16 */

#ifndef BASE_16C
#define BASE_16C "0123456789ABCDEF"
#endif /* ifndef BASE_16C */

ssize_t ft_putnbr_baseu(int fd, unsigned long nbr, const char *base);
ssize_t ft_putnbr_base(int fd, int nbr, const char *base);
ssize_t ft_putstr_ssize(int fd, const char *str);
ssize_t ft_putchar_ssize(int fd, char c);
int ft_printf(const char *format, ...);
int ft_printf_fd(int fd, const char *format, ...);

#endif /* ifndef FT_PRINTF_H */
