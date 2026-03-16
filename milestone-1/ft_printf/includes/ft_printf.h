/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 19:35:33 by elagouch          #+#    #+#             */
/*   Updated: 2026/03/16 18:29:08 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
#define FT_PRINTF_H

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

// formatting flags
typedef struct s_format {
  int minus;
  int zero;
  int hash;
  int space;
  int plus;
  int width;     // min width
  int precision; // precision (-1 means not specified)
  char type;     // conversion type (c, s, p, d, etc.)
} t_format;

// rewrites of classic funcs for our use case
ssize_t pfputnbru_base(int fd, unsigned long nbr, const char *base);
ssize_t pfputnbr_base(int fd, int nbr, const char *base);
ssize_t pfputstr(int fd, const char *str);
ssize_t pfputchar(int fd, char c);

// utils
t_format parse_format(const char **format);
// displaying
long print_hex(int fd, t_format *fmt, unsigned int nbr);
long print_signed(int fd, t_format *fmt, int nbr);
long print_string(int fd, t_format *fmt, const char *str);
long print_padding(int fd, int current_len, int target_width, char c);

// exposed functions
int ft_printf(const char *format, ...) __attribute__((format(printf, 1, 2)));
int ft_printf_fd(int fd, const char *format, ...)
    __attribute__((format(printf, 2, 3)));

#endif /* ifndef FT_PRINTF_H */
