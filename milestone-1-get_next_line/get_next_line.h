/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 09:29:29 by elagouch          #+#    #+#             */
/*   Updated: 2024/11/29 12:12:56 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <limits.h>
# include <unistd.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

unsigned int		ft_strlcat(char *dst, const char *src, size_t size);
unsigned int		ft_strlcpy(char *dst, const char *src, size_t size);
size_t				ft_strlen(const char *str);
void				*ft_calloc(size_t nmemb, size_t size);
char				*ft_substr(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
char				*get_remaining_buffer(char **buffer);
char				*ft_strchr(const char *s, int c);
char				*ft_strdup(const char *s);
char				*get_next_line(int fd);

#endif
