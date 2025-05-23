/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   h_types.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 13:41:58 by elagouch          #+#    #+#             */
/*   Updated: 2025/05/11 19:01:07 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef H_TYPES_H
# define H_TYPES_H

typedef struct s_coords
{
	int				x;
	int				y;
}					t_coords;
typedef enum s_tile
{
	epty = 0,
	obst = 1,
	full = 9,
}					t_tile;
typedef struct s_tiles
{
	char			epty;
	char			obst;
	char			full;
}					t_tiles;
typedef struct s_map
{
	t_coords		coords;
	t_tiles			tiles;
	t_tile			**map;
}					t_map;
typedef enum e_bool
{
	false,
	true
}					bool;
typedef struct s_strsplit_args
{
	unsigned long	*i;
	unsigned long	*j;
	char			**split;
	char			*str;
	char			*c;
	int				*index;
}					t_strsplit_args;

#endif
