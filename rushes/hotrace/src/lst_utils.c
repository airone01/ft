#include "hotrace.h"
#include "libft.h"

t_hlist *h_lstnew(char *key, char *value) {
  t_hlist *new;

  new = malloc(sizeof(t_hlist));
  if (!new)
    return (NULL);
  new->key = key;
  new->value = value;
  new->next = NULL;
  return (new);
}

t_hlist *h_lstlast(t_hlist *lst) {
  t_hlist *last;

  if (!lst)
    return (NULL);
  last = lst;
  while (last->next)
    last = last->next;
  return (last);
}

void h_lstadd_front(t_hlist **lst, t_hlist *new) {
  if (!lst)
    return;
  if (!*lst) {
    *lst = new;
    return;
  }
  new->next = *lst;
  *lst = new;
}

t_hlist *find_node(t_hlist *head, char *key) {
  t_hlist *current;

  current = head;
  while (current != NULL) {
    if (ft_strcmp(current->key, key) == 0)
      return (current);
    current = current->next;
  }
  return (NULL);
}

void free_list(t_hlist **lst) {
  t_hlist *cpy;

  if (!lst || !(*lst))
    return;
  while (*lst != NULL) {
    cpy = *lst;
    *lst = cpy->next;
    free(cpy);
  }
  *lst = NULL;
}
