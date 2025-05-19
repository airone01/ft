/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rush_find_word.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 17:11:51 by elagouch          #+#    #+#             */
/*   Updated: 2024/11/19 12:19:45 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "h_main.h"

/*
 * Finds the word in the cube corresponding to the searched number.
 *
 * @param	cube	the "cube" mentionned above
 * @param	len		length of the cube on th x axis
 * @param	u		"unit"		(times of `qty`)
 * @param	qty		"quantity"	(power of thousands)
 *
 * @returns	the word corresponding to what we search for
 * @returns	if not found, `NULL`
 *
 * ## The cube
 *
 * `x`: lines
 * `y`: the two strings (left and right) for each line
 * 	(`to_find` being the left-side string and the
 * 	"word" being the righ-side one)
 * `z`: (disregard) the chars for each string
 *
 * ```
 *     #---y---#
 *    /|      /|
 *   z x     z x
 *  /  |    /  |
 * #===y===#---#
 * |  /    |  /
 * x z     x z
 * |/      |/
 * #===y===#
 * ```
 */
char	*find_word(char ***cube, int len, int u, int qty)
{
	int		i;
	char	*a_to_find;
	char	*head;

	head = ft_itoa(u);
	a_to_find = ft_strnew(1 + ft_strlen(head) + (3 * qty));
	ft_strcat(a_to_find, head);
	i = 0;
	while (i < qty)
	{
		ft_strcat(a_to_find, "000");
		i++;
	}
	i = 0;
	while (i < len)
	{
		if (ft_strcmp(cube[i][0], a_to_find) == 0)
		{
			free(a_to_find);
			return (cube[i][1]);
		}
		i++;
	}
	free(a_to_find);
	return (NULL);
}
