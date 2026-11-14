#ifndef LIBASM_TESTS_TEST_H
#define LIBASM_TESTS_TEST_H

#include <sys/types.h>

extern size_t ft_strlen(const char *s);
extern char *ft_strcpy(const char *dest, const char *src);
extern int ft_strcmp(const char *s1, const char *s2);
extern ssize_t ft_write(int fildes, const void *buf, size_t nbyte);
extern ssize_t ft_read(int fildes, void *buf, size_t nbyte);
extern char *ft_strdup(const char *s);
extern int ft_atoi_base(char *str, char *base);
extern int g_invalid_base;
extern int g_no_match;

typedef struct s_list {
  void *data;
  struct s_list *next;
} t_list;

extern void ft_list_push_front(t_list **begin_list, void *data);
extern int ft_list_size(t_list *begin_list);
extern void ft_list_sort(t_list **begin_list, int (*cmp)(void));
extern void ft_list_remove_if(t_list **begin_list, void *data_ref,
                              int (*cmp)(void), void (*free_fct)(void *));

#endif /* LIBASM_TESTS_TEST_H */
