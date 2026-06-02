
#include "h_main.h"

/*
 * Puts a string to stdout.
 */
void ft_putstr(char *str) { write(1, str, ft_strlen(str)); }
