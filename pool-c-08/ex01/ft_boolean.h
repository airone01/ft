/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_boolean.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 09:37:58 by elagouch          #+#    #+#             */
/*   Updated: 2024/11/19 11:29:46 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_BOOLEAN_H
# define FT_BOOLEAN_H

# include <unistd.h>

typedef enum e_bool
{
	FALSE = 0,
	TRUE = 1,
}	t_bool;

# define SUCCESS 0

# define ODD_MSG "I have an odd number of arguments."
# define EVEN_MSG "I have an even number of arguments."

// # define EVEN(nbr) nbr % 2 == 0

#endif
