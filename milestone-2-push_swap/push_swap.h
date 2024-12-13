/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 18:18:47 by elagouch          #+#    #+#             */
/*   Updated: 2024/12/13 14:11:09 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include "libft/libft.h"
# include "printf/ft_printf.h"
# include <unistd.h>

typedef struct s_stack
{
    ssize_t			content;
    struct s_stack	*next;
    struct s_stack	*prev;
}					t_stack;

// ### STACK FUNCTIONS ###
// -> Creating
t_stack				*stack_from_strings(char **strings);
t_stack				*stack_add_front(t_stack *stack, ssize_t nbr);
void				stack_add_back(t_stack *stack, ssize_t nbr);
// -> Removing
void				stack_del_one(t_stack *stack);
void				stack_clear(t_stack *stack);
// -> Misc.
void				stack_iter(t_stack *stack, void (*f)(t_stack *));
ssize_t             stack_max(t_stack *stack);
ssize_t             stack_min(t_stack *stack);
size_t              stack_size(t_stack *stack);

// ### STACK MANIPULATION ###
void                sa(t_stack *stack_a);
void                sb(t_stack *stack_b);
void                ss(t_stack *stack_a, t_stack *stack_b);
void                pa(t_stack **stack_a, t_stack **stack_b);
void                pb(t_stack **stack_a, t_stack **stack_b);
void                ra(t_stack **stack_a);
void                rb(t_stack **stack_b);
void                rr(t_stack **stack_a, t_stack **stack_b);
void                rra(t_stack **stack_a);
void                rrb(t_stack **stack_b);
void                rrr(t_stack **stack_a, t_stack **stack_b);

// ### PARSING ###
t_stack				*parse_stdin(int argc, char **argv);
t_stack				*stack_last(t_stack *stack);
t_stack				*stack_new(ssize_t nbr);

// ### SORTING ###
void                sort_count(t_stack *stack, size_t dth);
void                sort_radix(t_stack *stack);

// ### DISPLAYING ###
void				stack_print(t_stack *stack);
void				std_error(void);

#endif
