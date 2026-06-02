/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   h_str.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 22:45:53 by elagouch          #+#    #+#             */
/*   Updated: 2024/11/19 12:18:40 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
char **ft_split2(char *str, char *charset);
char **ft_split(char *str, char *charset);
char *ft_strncpy(char *dest, char *src, unsigned int n);
char *ft_strjoin(int size, char **strs, char *sep);
char *ft_strcat(char *dest, char *src);
char *ft_strcpy(char *dest, char *src);
char *ft_strnew(int size);
int check_charset(char *str, char *charset, int i);
int count_words(char *str, char *charset);

#endif
