
#include "push_swap.h"

/**
 * Tests a stack against the project requirements
 * @param	stack	Stack
 * @returns			0 on legit, else 1
 */
int	stack_legit(t_stack *stack)
{
	if (!stack || stack_size(stack) <= 1)
		return (stack_clear_error(stack), 1);
	stack_pos(&stack);
	if (stack_dupes(stack))
		return (stack_clear_error(stack), 1);
	return (0);
}
