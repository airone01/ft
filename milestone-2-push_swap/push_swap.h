/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 18:18:47 by elagouch          #+#    #+#             */
/*   Updated: 2024/12/20 19:03:04 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include "libft/libft.h"
# include <unistd.h>

typedef struct s_stack
{
	ssize_t			val;
	ssize_t			idx;
	ssize_t			pos;
	ssize_t			t_pos;
	ssize_t			cost_a;
	ssize_t			cost_b;
	struct s_stack	*next;
}					t_stack;

// ### STACK FUNCTIONS ###
// -> Creating
void				stack_add_back(t_stack *stack, ssize_t nbr);
// -> Removing
void				stack_del_one(t_stack *stack);
void				stack_clear(t_stack *stack);
// -> Misc.
t_stack				*stack_maxn(t_stack *stack);
size_t				stack_size(t_stack *stack);
void				stack_iter(t_stack *stack, void (*f)(t_stack *));
void				stack_indexes(t_stack *stack, size_t len);

// ### STACK MANIPULATION ###
void				sa(t_stack *stack_a);
void				sb(t_stack *stack_b);
void				ss(t_stack *stack_a, t_stack *stack_b);
void				pa(t_stack **stack_a, t_stack **stack_b);
void				pb(t_stack **stack_a, t_stack **stack_b);
void				ra(t_stack **stack_a);
void				rb(t_stack **stack_b);
void				rr(t_stack **stack_a, t_stack **stack_b);
void				rra(t_stack **stack_a);
void				rrb(t_stack **stack_b);
void				rrr(t_stack **stack_a, t_stack **stack_b);

// ### PARSING ###
t_stack				*parse_stdin(int argc, char **argv);
t_stack				*stack_before_last(t_stack *stack);
t_stack				*stack_last(t_stack *stack);
t_stack				*stack_new(ssize_t nbr);

// ### SORTING ###
// void                sort_count(t_stack *stack, size_t dth);
ssize_t				stack_lowest_pos(t_stack **stack);
ssize_t				stack_sorted(t_stack *stack);
void				move(t_stack **stack_a, t_stack **stack_b, ssize_t cost_a,
						ssize_t cost_b);
void				sort_large(t_stack **stack_a, t_stack **stack_b);
void				stack_target_pos(t_stack **stack_a, t_stack **stack_b);
void				push_save_three(t_stack **stack_a, t_stack **stack_b);
void				cheapest_move(t_stack **stack_a, t_stack **stack_b);
void				cost(t_stack **stack_a, t_stack **stack_b);
void				stack_shift(t_stack **stack);
void				sort_tiny(t_stack **stack);

// ### DISPLAYING ###
void				std_error(void);

// ### MISC ###
ssize_t				ft_abs(ssize_t nb);

#endif
