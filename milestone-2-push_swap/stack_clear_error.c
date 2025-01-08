
#include "push_swap.h"

/**
* Clears the stack and errors out
* @param    t_stack    Stack
*/
void	stack_clear_error(t_stack *stack_a)
{
    stack_clear(stack_a);
    std_error();
}
