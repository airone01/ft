
#include "libft.h"

t_list *ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *)) {
  t_list *new_list;
  t_list *new_node;
  void *content;

  if (!lst || !f || !del)
    return (0);
  new_list = 0;
  while (lst) {
    content = f(lst->content);
    new_node = ft_lstnew(content);
    if (!new_node) {
      del(content);
      ft_lstclear(&new_list, del);
      return (0);
    }
    ft_lstadd_back(&new_list, new_node);
    lst = lst->next;
  }
  return (new_list);
}
