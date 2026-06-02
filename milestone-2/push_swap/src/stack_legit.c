
#include "push_swap.h"

/**
 * Tests a stack against the project requirements
 * @param	stack	Stack
 * @returns			0 on legit, else 1
 */
int stack_legit(t_stack *stack) {
  long size;

  if (!stack)
    return (stack_clear_error(stack), 1);
  size = (long)stack_size(stack);
  if (size < 1)
    return (stack_clear_error(stack), 1);
  if (size <= 1)
    return (stack_clear(stack), 1);
  stack_pos(&stack);
  if (stack_dupes(stack))
    return (stack_clear_error(stack), 1);
  return (0);
}
