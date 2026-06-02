
#include "push_swap.h"

/**
 * Checks if a stack is sorted
 * @param   stack   Stack
 * @return          Whether the stack is sorted or not
 */
ssize_t stack_sorted(t_stack *stack) {
  while (stack->next) {
    if (stack->val > stack->next->val)
      return (0);
    stack = stack->next;
  }
  return (1);
}
