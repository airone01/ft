
#include "libft.h"

t_list *ft_lstat(t_list *lst, size_t index) {
  size_t i;

  i = 0;
  while (lst && i < index) {
    lst = lst->next;
    i++;
  }
  return (lst);
}
