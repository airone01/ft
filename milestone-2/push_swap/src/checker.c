
#include "push_swap.h"
#include <errno.h>

int run_program(int argc, char **argv) {
  t_stack *stack_a;
  long sorted;

  if (!args_legit(argc, argv))
    return (std_error(), 1);
  stack_a = parse_stdin(argc, argv);
  if (stack_legit(stack_a))
    return (EINVAL);
  if (execute(&stack_a))
    return (stack_clear_error(stack_a), 1);
  sorted = stack_sorted(stack_a);
  stack_clear(stack_a);
  if (sorted)
    return ((void)write(1, "OK\n", 3), 0);
  return ((void)write(1, "KO\n", 3), 1);
}

int main(int argc, char **argv) {
  if (argc <= 1)
    return (1);
  argc--;
  argv++;
  return (run_program(argc, argv));
}
