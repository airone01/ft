/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   h_rush.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@42>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 23:20:38 by elagouch          #+#    #+#             */
/*   Updated: 2024/09/29 23:24:14 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef H_RUSH_H
# define H_RUSH_H

// Rush-specific
char	*find_word(char ***cube, int len, int u, int qty);
struct	s_lang_args
{
	char	***cube;
	char	*nbr;
	int		len;
	int		ite;
	int		qty;
};

#endif
