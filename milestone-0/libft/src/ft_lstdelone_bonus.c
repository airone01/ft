
#include "libft.h"

void ft_lstdelone(t_list *lst, void (*del)(void *)) {
  if (!del || !lst)
    return;
  if (lst->content)
    del(lst->content);
  free(lst);
  lst = NULL;
}
