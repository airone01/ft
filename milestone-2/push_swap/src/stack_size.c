
#include "push_swap.h"

/**
 * Gets the size of a stack
 * @param   stack   Stack
 * @return          The size of the stack
 */
size_t stack_size(t_stack *stack) {
  size_t size;
  t_stack *current;

  size = 0;
  current = stack;
  while (current) {
    size++;
    current = current->next;
  }
  return (size);
}
