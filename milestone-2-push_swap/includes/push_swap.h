/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 18:18:47 by elagouch          #+#    #+#             */
/*   Updated: 2025/03/04 18:04:09 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include "get_next_line.h"
# include "libft.h"
# include <fcntl.h>
# include <limits.h>
# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 8
# endif

# ifndef FD_SIZE
#  define FD_SIZE 1
# endif

typedef struct s_stack
{
	long			val;
	long			idx;
	long			pos;
	long			t_pos;
	long			cost_a;
	long			cost_b;
	struct s_stack	*next;
}					t_stack;

// ### STACK FUNCTIONS ###
// -> Creating
void				stack_add_back(t_stack *stack, long nbr);
// -> Removing
void				stack_clear(t_stack *stack);
// -> Misc.
unsigned long		args_legit(int argc, char **argv);
unsigned long		stack_size(t_stack *stack);
t_stack				*stack_maxn(t_stack *stack);
void				stack_iter(t_stack *stack, void (*f)(t_stack *));
void				stack_indexes(t_stack *stack, unsigned long len);

// ### STACK MANIPULATION ###
void				sa(t_stack *stack_a, unsigned long display);
void				sb(t_stack *stack_b, unsigned long display);
void				ss(t_stack *stack_a, t_stack *stack_b,
						unsigned long display);
void				pa(t_stack **stack_a, t_stack **stack_b,
						unsigned long display);
void				pb(t_stack **stack_a, t_stack **stack_b,
						unsigned long display);
void				ra(t_stack **stack_a, unsigned long display);
void				rb(t_stack **stack_b, unsigned long display);
void				rr(t_stack **stack_a, t_stack **stack_b,
						unsigned long display);
void				rra(t_stack **stack_a, unsigned long display);
void				rrb(t_stack **stack_b, unsigned long display);
void				rrr(t_stack **stack_a, t_stack **stack_b,
						unsigned long display);

// ### PARSING ###
t_stack				*parse_stdin(int argc, char **argv);
t_stack				*stack_before_last(t_stack *stack);
t_stack				*stack_last(t_stack *stack);
t_stack				*stack_new(long nbr);
long				stack_dupes(t_stack *s1);
void				stack_pos(t_stack **stack);
int					stack_legit(t_stack *stack);

// ### SORTING ###
// void                sort_count(t_stack *stack, unsigned long dth);
long				stack_lowest_pos(t_stack **stack);
long				stack_sorted(t_stack *stack);
void				move(t_stack **stack_a, t_stack **stack_b, long cost_a,
						long cost_b);
void				sort_large(t_stack **stack_a, t_stack **stack_b);
void				stack_target_pos(t_stack **stack_a, t_stack **stack_b);
void				push_save_three(t_stack **stack_a, t_stack **stack_b);
void				cheapest_move(t_stack **stack_a, t_stack **stack_b);
void				cost(t_stack **stack_a, t_stack **stack_b);
void				stack_shift(t_stack **stack);
void				sort_tiny(t_stack **stack);

// ### DISPLAYING ###
void				std_error(void);
void				stack_clear_error(t_stack *stack_a);

// ### MISC ###
char				*get_next_line(int fd);

// ### BONUSES ###
long				execute(t_stack **stack_a);

#endif
