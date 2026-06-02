
#include "push_swap.h"

/**
 * Deletes and frees a stack
 * @param   stack   Stack to completely delete
 */
void stack_clear(t_stack *stack) {
  t_stack *current;
  t_stack *next;

  if (!stack)
    return;
  current = stack;
  while (current) {
    next = current->next;
    free(current);
    current = next;
  }
}
