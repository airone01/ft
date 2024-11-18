/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   h_str.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@42>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 10:50:48 by elagouch          #+#    #+#             */
/*   Updated: 2024/10/01 10:49:40 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef H_STR_H
# define H_STR_H

// STDIN manipulations
void			ft_putstr(char *str);
void			ft_puterr(char *str);
// Strings manipulation
unsigned int	ft_strlcat(char *dest, char *src, unsigned int size);
t_bool			char_is_alpha(char c);
t_bool			char_is_num(char c);
void			ft_putchar(char c);
char			*ft_strncpy(char *dest, char *src, unsigned int n);
char			*ft_strjoin(int size, char **strs, char *sep);
char			*ft_strcut(char *str, int start, int finish);
char			*ft_strcat(char *dest, char *src);
char			*ft_strcpy(char *dest, char *src);
char			**ft_strsplit(char *str, char c);
char			*ft_strdup(char *src);
char			*ft_strnew(int size);
int				ft_strcount_words_sep(char *str, char sep);
int				ft_strcmp(char *s1, char *s2);
int				ft_strcount_words(char *str);
int				ft_strlen(char *str);

#endif
