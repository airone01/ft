
#include "push_swap.h"

/**
 * Pushes all the elements of Stack A into Stack B, except for the three last.
 * It pushes the lower values first for optimization reasons.
 * @param   len     Length of stack A
 * @param   stack_a Stack A
 * @param   stack_b Stack B
 */
void push_save_three(t_stack **stack_a, t_stack **stack_b) {
  size_t pushed;
  size_t len;
  size_t i;

  i = 0;
  pushed = 0;
  len = stack_size(*stack_a);
  while (len > 6 && i < len && pushed < len / 2) {
    if ((*stack_a)->idx <= (ssize_t)len / 2) {
      pb(stack_a, stack_b, 1);
      pushed++;
    } else
      ra(stack_a, 1);
    i++;
  }
  while (len - pushed > 3) {
    pb(stack_a, stack_b, 1);
    pushed++;
  }
}
