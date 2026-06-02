
#ifndef H_STR_H
#define H_STR_H

#include <stddef.h>

// From libft
char *ft_itoa(int n);
int ft_atoi(const char *nptr);
size_t ft_strlcat(char *dst, const char *src, size_t size);
char *ft_strdup(const char *s);
int ft_strcmp(const char *s1, const char *s2);
size_t ft_strlen(const char *str);
// STDIN manipulations
void ft_putstr(char *str);
// Strings manipulation — local implementations
char **ft_split_rush2(char *str, char *charset);
char **ft_split_rush(char *str, char *charset);
char *ft_strncpy(char *dest, char *src, unsigned int n);
char *ft_strjoin(int size, char **strs, char *sep);
char *ft_strcat(char *dest, char *src);
char *ft_strcpy(char *dest, char *src);
char *ft_strnew(int size);
int check_charset(char *str, char *charset, int i);
int count_words(char *str, char *charset);

#endif
