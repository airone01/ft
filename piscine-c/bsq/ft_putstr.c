
#include "h_main.h"

/*
 * Puts a string to stdout.
 */
void ft_putchar(char c) { write(1, &c, 1); }

/*
 * Puts a string to stdout.
 */
void ft_putstr(char *str) { write(1, str, ft_strlen(str)); }

/*
 * Puts a string to stderr.
 */
void ft_puterr(char *str) { write(2, str, ft_strlen(str)); }
