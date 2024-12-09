/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 09:29:29 by elagouch          #+#    #+#             */
/*   Updated: 2024/11/29 19:13:41 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <limits.h>
# include <stdint.h>
# include <stdlib.h>
# include <unistd.h>

unsigned int		ft_strlcat(char *dst, const char *src, size_t size);
unsigned int		ft_strlcpy(char *dst, const char *src, size_t size);
ssize_t				read_until_nl(int fd, char **line);
size_t				ft_strlen(const char *str);
void				*ft_calloc(size_t nmemb, size_t size);
void				ft_memset(void *s, int c, size_t n);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strchr(const char *s, int c);
char				*ft_strdup(const char *s);
char				*get_next_line(int fd);

#endif
