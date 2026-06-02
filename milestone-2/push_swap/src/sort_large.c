
#include "push_swap.h"

void sort_large(t_stack **stack_a, t_stack **stack_b) {
  push_save_three(stack_a, stack_b);
  sort_tiny(stack_a);
  while (*stack_b) {
    stack_target_pos(stack_a, stack_b);
    cost(stack_a, stack_b);
    cheapest_move(stack_a, stack_b);
  }
  if (!stack_sorted(*stack_a))
    stack_shift(stack_a);
}
