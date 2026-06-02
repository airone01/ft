
#include "push_swap.h"

/**
 * Appends a new number at the end of a stack
 * @param	stack	Stack
 * @param	nbr		Number to add
 */
void stack_add_back(t_stack *stack, long nbr) {
  t_stack *last;
  t_stack *tmp;

  if (!stack)
    return;
  tmp = stack_new(nbr);
  if (!tmp)
    return;
  last = stack_last(stack);
  last->next = tmp;
}
