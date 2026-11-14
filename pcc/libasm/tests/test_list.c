#include "test.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
  t_list *list = NULL;

  /* ft_list_size: NULL list */
  assert(ft_list_size(NULL) == 0);

  /* ft_list_push_front: single push */
  ft_list_push_front(&list, "hello");
  assert(ft_list_size(list) == 1);
  assert(strcmp((char *)list->data, "hello") == 0);

  /* ft_list_push_front: second push goes to front */
  ft_list_push_front(&list, "world");
  assert(ft_list_size(list) == 2);
  assert(strcmp((char *)list->data, "world") == 0);
  assert(strcmp((char *)list->next->data, "hello") == 0);

  /* ft_list_push_front: third push */
  ft_list_push_front(&list, "!");
  assert(ft_list_size(list) == 3);

  /* ft_list_sort: sort ["!", "world", "hello"] ascending by strcmp */
  ft_list_sort(&list, (int (*)())ft_strcmp);
  assert(strcmp((char *)list->data, "!") == 0);
  assert(strcmp((char *)list->next->data, "hello") == 0);
  assert(strcmp((char *)list->next->next->data, "world") == 0);

  /* ft_list_sort: already-sorted list is stable */
  ft_list_sort(&list, (int (*)())ft_strcmp);
  assert(strcmp((char *)list->data, "!") == 0);

  /* free the sorted list before remove_if tests */
  while (list) {
    t_list *n = list->next;
    free(list);
    list = n;
  }

  /* ft_list_remove_if: build ["a", "b", "a", "c"] using strdup data */
  list = NULL;
  ft_list_push_front(&list, strdup("c"));
  ft_list_push_front(&list, strdup("a"));
  ft_list_push_front(&list, strdup("b"));
  ft_list_push_front(&list, strdup("a"));
  /* list is now: a -> b -> a -> c */

  /* remove all "a" nodes */
  ft_list_remove_if(&list, "a", (int (*)())ft_strcmp, free);
  assert(ft_list_size(list) == 2);
  assert(strcmp((char *)list->data, "b") == 0);
  assert(strcmp((char *)list->next->data, "c") == 0);

  /* remove all remaining nodes */
  ft_list_remove_if(&list, "b", (int (*)())ft_strcmp, free);
  ft_list_remove_if(&list, "c", (int (*)())ft_strcmp, free);
  assert(list == NULL);

  return 0;
}
