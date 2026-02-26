libasm
======

A library of basic functions, written in assembly.

Assembly specifications
-----------------------

This project is programmed for baseline x86_64 with the System V AMD64 convention, for the GNU/Linux ABI.
The Intel syntax is the one used, as required by the subject.
This is not programmed for any AVX extension.

Provided functions
------------------

The functions provided by this project are the following:

- ft_strlen (man 3 strlen)
- ft_strcpy (man 3 strcpy)
- ft_strcmp (man 3 strcmp)
- ft_write (man 2 write)
- ft_read (man 2 read)
- ft_strdup (man 3 strdup, call to malloc allowed)

And the bonus functions are as follow:

- ft_atoi_base
  - `int ft_atoi_base(char *str, char *base);`
- ft_list_push_front
  - `void ft_list_push_front(t_list **begin_list, void *data);`
- ft_list_size
  - `int ft_list_size(t_list *begin_list);`
- ft_list_sort
  - `void ft_list_sort(t_list **begin_list, int (*cmp)());`
  - The function pointed to by cmp will be used as:
    - `(*cmp)(list_ptr->data, list_other_ptr->data);`
- ft_list_remove_if
  - `void ft_list_remove_if(t_list **begin_list, void *data_ref, int (*cmp)(), void (*free_fct)(void *));`
  - The functions pointed to by cmp will be used respectively as:
    - `(*cmp)(list_ptr->data, data_ref);`
    - `(*free_fct)(list_ptr->data);`
