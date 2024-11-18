/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   h_str.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@42>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 22:45:53 by elagouch          #+#    #+#             */
/*   Updated: 2024/09/29 23:28:47 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef H_STR_H
#define H_STR_H

// Strings <-> numbers
char			*ft_itoa(int nb);
long			ft_atoi(char *str);
// STDIN manipulations
void			ft_putstr(char *str);
// Strings manipulation
unsigned int	ft_strlcat(char *dest, char *src, unsigned int size);
char			**ft_split2(char *str, char *charset);
char			**ft_split(char *str, char *charset);
char			*ft_strncpy(char *dest, char *src, unsigned int n);
char			*ft_strjoin(int size, char **strs, char *sep);
char			*ft_strcat(char *dest, char *src);
char			*ft_strcpy(char *dest, char *src);
char			*ft_strdup(char *src);
char			*ft_strnew(int size);
int				ft_strcmp(char *s1, char *s2);
int				ft_strlen(char *str);
int				check_charset(char *str, char *charset, int i);
int				count_words(char *str, char *charset);

#endif
