/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_boolean.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 09:37:58 by elagouch          #+#    #+#             */
/*   Updated: 2025/01/02 23:19:31 by elagouch         ###   ########.fr       */
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

# define EVEN(nbr)	((nbr % 2) == 0 ? TRUE : FALSE)

#endif
