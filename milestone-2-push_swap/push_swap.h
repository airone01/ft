/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 18:18:47 by elagouch          #+#    #+#             */
/*   Updated: 2024/12/11 17:20:58 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include "libft/libft.h"
# include "printf/ft_printf.h"
# include <unistd.h>

typedef struct s_stack
{
	long			content;
	struct s_stack	*next;
}					t_stack;

t_stack				*stack_add_front(t_stack *stack, long nbr);
t_stack				*stack_from_stdin(int argc, char **argv);
t_stack				*stack_from_strings(char **strings);
t_stack				*parse_stdin(int argc, char **argv);
t_stack				*stack_last(t_stack *stack);
t_stack				*stack_new(long nbr);
void				stack_iter(t_stack *stack, void (*f)(t_stack *));
void				stack_add_back(t_stack *stack, long nbr);
void				stack_del_one(t_stack *stack);
void				stack_clear(t_stack *stack);
void				stack_print(t_stack *stack);
void				std_error(void);

#endif
