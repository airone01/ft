
#include "push_swap.h"

/**
 * Calls a function iteratively on every stack layer
 * @param   stack   Stack
 * @param   f       Function
 */
void stack_iter(t_stack *stack, void (*f)(t_stack *)) {
  f(stack);
  if (stack->next)
    stack_iter(stack->next, f);
}
