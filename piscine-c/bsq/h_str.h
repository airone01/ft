#ifndef H_STR_H
#define H_STR_H

#include <stdbool.h>

bool char_is_alpha(char c);
bool char_is_num(char c);
char *ft_strnew(int size);
int ft_strcount_words_sep(char *str, char sep);
int ft_strcount_words(char *str);

#endif
