/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 18:18:47 by elagouch          #+#    #+#             */
/*   Updated: 2025/01/17 14:59:32 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include "../milestone-0-libft/libft.h"                 // GPM!
# include "../milestone-1-get_next_line/get_next_line.h" // GPM!
// GPM@ .# include "libft/libft.h"
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
void				stack_clear(t_stack *stack);
// -> Misc.
t_stack				*stack_maxn(t_stack *stack);
size_t				args_legit(int argc, char **argv);
size_t				stack_size(t_stack *stack);
void				stack_iter(t_stack *stack, void (*f)(t_stack *));
void				stack_indexes(t_stack *stack, size_t len);

// ### STACK MANIPULATION ###
void				sa(t_stack *stack_a, size_t display);
void				sb(t_stack *stack_b, size_t display);
void				ss(t_stack *stack_a, t_stack *stack_b, size_t display);
void				pa(t_stack **stack_a, t_stack **stack_b, size_t display);
void				pb(t_stack **stack_a, t_stack **stack_b, size_t display);
void				ra(t_stack **stack_a, size_t display);
void				rb(t_stack **stack_b, size_t display);
void				rr(t_stack **stack_a, t_stack **stack_b, size_t display);
void				rra(t_stack **stack_a, size_t display);
void				rrb(t_stack **stack_b, size_t display);
void				rrr(t_stack **stack_a, t_stack **stack_b, size_t display);

// ### PARSING ###
t_stack				*parse_stdin(int argc, char **argv);
t_stack				*stack_before_last(t_stack *stack);
t_stack				*stack_last(t_stack *stack);
t_stack				*stack_new(ssize_t nbr);
ssize_t				stack_dupes(t_stack *s1);
void				stack_pos(t_stack **stack);
int					stack_legit(t_stack *stack);

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
void				stack_clear_error(t_stack *stack_a);

// ### MISC ###
char				*get_next_line(int fd);

// ### BONUSES ###
size_t				execute(t_stack **stack_a);
// GPM@ .				ft_abs(ssize_t nb);

// ### LIBFT ###
// GPM@ .ssize_t				ft_abs(ssize_t nb);
// GPM@ .void				*ft_calloc(size_t nmemb, size_t size);
// GPM@ .char				**ft_split(char *str, char c);
// GPM@ .long				ft_atol(const char *nptr);
// GPM@ .int					ft_isdigit(int c);

#endif
