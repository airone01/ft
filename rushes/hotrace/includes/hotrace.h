/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hotrace.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anfichet <anfichet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 11:01:36 by elagouch          #+#    #+#             */
/*   Updated: 2025/02/23 23:39:26 by anfichet         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef HOTRACE_H
# define HOTRACE_H

# include <fcntl.h>
# include <stdbool.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# ifndef TBL_SIZE
#  define TBL_SIZE 150000
# endif

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 128
# endif

# ifndef GNL_INITIAL_CAPACITY
#  define GNL_INITIAL_CAPACITY 128
# endif

# ifndef GNL_GROWTH_FACTOR
#  define GNL_GROWTH_FACTOR 2
# endif

typedef enum e_error
{
	ERR = -1,
	ERR_ARG_INVALID,
	ERR_MALLOC,
	ERR_FILE_OPEN,
}					t_error;

typedef struct s_file_content
{
	char			**lines;
	size_t			size;
	size_t			capacity;
}					t_file_content;

typedef struct s_list
{
	char			*key;
	char			*value;
	struct s_list	*next;
}					t_list;

int					process_input(t_list *tbl[TBL_SIZE]);
int					process_line_main(t_list *tbl[TBL_SIZE], \
					char *line, bool *reading_pairs);
int					process_pair(t_list *tbl[TBL_SIZE], char *key);
void				handle_request(t_list *tbl[TBL_SIZE], char *line);
int					handle_key_value(t_list *tbl[TBL_SIZE], \
					char *key, char *value);

/* List */
t_list				*ft_lstnew(char *key, char *value);
t_list				*ft_lstlast(t_list *lst);
void				ft_lstadd_front(t_list **lst, t_list *new);

/* Memory */
void				final_countdown(t_list *tbl[TBL_SIZE]);
void				free_2d_array(void **ptrs);

/* Errors handling */
void				error(char *msg, int err);

/* Parsing */
bool				is_empty_line(char *line);
char				**parse_content(void *tbl, char **content);
char				**read_entire_file(int fd);
char				**init_requests(size_t size);
char				*strip_newline(char *str);
int					handle_pairs(void *tbl, char **content, int *i);
int					count_requests(char **content, int start);

/*/ Hash */
uint32_t			fnv1a_hash(const void *data, size_t size);
int					hash_find_index(char *key);

/* Table */
bool				append_to_table(t_list *tbl[TBL_SIZE], char *key,
						char *value);
t_list				*find_node(t_list *head, char *key);
t_list				*tbl_find_node(t_list *tbl[TBL_SIZE], char *key);

/* Get next line */
t_file_content		*init_file_content(void);
char				*process_read(int fd, char *buffer, char *temp);
char				*read_buffer(int fd, char *buffer);
char				*initialize_buffer(char *buffer);
char				*get_next_line(int fd);
int					append_line(t_file_content *content, char *line);
int					expand_capacity(t_file_content *content);

/* Libft utils */
void				ft_putendl_fd(const char *s, int fd);
void				*ft_calloc(size_t nmemb, size_t size);
char				*ft_strdup(const char *s);
char				*ft_strjoin(char const *s1, char const *s2);
unsigned long		ft_strlcpy(char *dst, const char *src, unsigned long size);
unsigned long		ft_strlcat(char *dst, const char *src, unsigned long size);
char				*ft_strchr(const char *s, char c);
size_t				ft_strlen(const char *str);
int					ft_strcmp(const char *s1, const char *s2);
void				ft_bzero(void *s, size_t n);
void				*ft_memcpy(void *dest, const void *src, size_t size);
void				ft_putstr_fd(char *s, int fd);

#endif
