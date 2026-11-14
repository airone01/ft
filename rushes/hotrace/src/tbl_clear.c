#include "hotrace.h"

/**
 * @brief	Frees all the memory allocated for the table.
 *
 * IT'S THE FINAL COUNTDOWN! 🎵
 *
 * @param	tbl		Table to clear.
 */
void final_countdown(t_hlist *tbl[TBL_SIZE]) {
  t_hlist *tmp;
  t_hlist *next;
  size_t i;

  i = 0;
  while (i < TBL_SIZE) {
    tmp = tbl[i];
    while (tmp) {
      next = tmp->next;
      if (tmp->key)
        free(tmp->key);
      if (tmp->value)
        free(tmp->value);
      free(tmp);
      tmp = next;
    }
    tbl[i] = NULL;
    i++;
  }
}
