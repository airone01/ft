/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 15:32:24 by elagouch          #+#    #+#             */
/*   Updated: 2025/02/19 16:40:56 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <limits.h> // LLONG_MAX
# include <stdint.h> // SIZE_MAX
# include <stdlib.h> // malloc, free
# include <unistd.h> // write

typedef enum e_bool
{
	false,
	true
}					t_bool;

// Bonuses
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

t_list				*ft_lstat(t_list *lst, unsigned long index);
t_list				*ft_lstmap(t_list *lst, void *(*f)(void *),
						void (*del)(void *));
t_list				*ft_lstnew(void *content);
t_list				*ft_lstlast(t_list *lst);
t_bool				ft_isalnum(char c);
t_bool				ft_isalpha(char c);
t_bool				ft_isascii(char c);
t_bool				ft_isdigit(char c);
t_bool				ft_isprint(char c);
void				ft_lstdelone(t_list *lst, void (*del)(void *));
void				ft_lstclear(t_list **lst, void (*del)(void *));
void				ft_lstiter(t_list *lst, void (*f)(void *));
void				ft_lstadd_front(t_list **lst, t_list *new);
void				ft_lstadd_back(t_list **lst, t_list *new);
unsigned long		ft_lstsize(t_list *lst);
// Standard C lib
unsigned long		ft_strlcat(char *dst, const char *src, unsigned long size);
unsigned long		ft_strlcpy(char *dst, const char *src, unsigned long size);
unsigned long		ft_strlen(const char *str);
void				*ft_recalloc(void *ptr, size_t old_size, size_t new_size);
void				*ft_memmove(void *dest, const void *src, size_t n);
void				*ft_memcpy(void *dest, const void *src, size_t n);
void				*ft_memchr(const void *s, uint8_t c, size_t n);
void				*ft_calloc(size_t nmemb, size_t size);
void				*ft_memset(void *s, uint8_t c, size_t n);
void				*ft_bzero(void *s, size_t n);
char				*ft_strnstr(const char *big, const char *little,
						unsigned long len);
char				*ft_strrchr(const char *s, char c);
char				*ft_strdup(const char *s);
int					ft_strncmp(const char *s1, const char *s2, unsigned long n);
int					ft_memcmp(const void *s1, const void *s2, unsigned long n);
int					ft_strcmp(const char *s1, const char *s2);
int					ft_atoi(const char *nptr);
int					ft_toupper(char c);
int					ft_tolower(char c);

//	Part 2
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
void				ft_putendl_fd(char *s, int fd);
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char *s, int fd);
void				ft_putnbr_fd(int n, int fd);
char				**ft_split(char *str, char c);
char				*ft_substr(char const *s, unsigned int start,
						unsigned long len);
char				*ft_strmapi(char const *s, char (*f)(unsigned long, char));
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strtrim(char *s1, char const *set);
char				*ft_itoa_base(int n, const char *b);
char				*ft_itoa(int n);

// Additional stuff by me
t_bool				ft_fuzzy_equals(double a, double b);
t_bool				ft_isspace(char c);
char				*ft_env_find(char **envp, const char *var);
char				*ft_strchr(const char *s, char c);
long				ft_atol(const char *nptr);
long				ft_abs(long n);

#endif
