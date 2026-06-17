#ifndef FT_PRINTF_BONUS_H
#define FT_PRINTF_BONUS_H

#include "ft_printf.h"
#include <stdint.h>

long print_unsigned(int fd, t_format *fmt, unsigned int nbr);
long print_char(int fd, t_format *fmt, char c);
long print_pointer(int fd, t_format *fmt, uintptr_t ptr);

#endif /* ifndef FT_PRINTF_BONUS_H */
