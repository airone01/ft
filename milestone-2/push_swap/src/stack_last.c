
#include "push_swap.h"

/**
 * Gets the last element in a stack recursively.
 * Will always return an element, except if stack is NULL.
 * @param   stack   Stack
 * @return          Last stack element
 */
t_stack *stack_last(t_stack *stack) {
  if (!stack)
    return (NULL);
  while (stack->next)
    stack = stack->next;
  return (stack);
}

/**
 * Gets the element before the last element in a stack recursively.
 * Will always return an element, except if stack is NULL.
 * @param   stack   Stack
 * @return          Pre-last stack element
 */
t_stack *stack_before_last(t_stack *stack) {
  if (!stack || !stack->next)
    return (NULL);
  while (stack->next->next)
    stack = stack->next;
  return (stack);
}
