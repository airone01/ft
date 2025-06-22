/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_mov.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 11:42:38 by elagouch          #+#    #+#             */
/*   Updated: 2025/06/17 19:14:44 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "player.h"

/*
** `l_mov_rot.c`
*/
void		rotate_l(t_player *player);
void		rotate_r(t_player *player);
bool		is_valid_position(t_data *data, double x, double y);

/*
** Move forward/backward along the direction vector
** Enhanced with door-aware collision detection
*/
static void	move_fw_bw(t_player *player, t_data *data)
{
	double	new_pos_x;
	double	new_pos_y;

	if (player->move_forward)
	{
		new_pos_x = player->pos_x + player->dir_x * player->move_speed;
		new_pos_y = player->pos_y - player->dir_y * player->move_speed;
		if (is_valid_position(data, new_pos_x, player->pos_y))
			player->pos_x = new_pos_x;
		if (is_valid_position(data, player->pos_x, new_pos_y))
			player->pos_y = new_pos_y;
	}
	if (player->move_backward)
	{
		new_pos_x = player->pos_x - player->dir_x * player->move_speed;
		new_pos_y = player->pos_y + player->dir_y * player->move_speed;
		if (is_valid_position(data, new_pos_x, player->pos_y))
			player->pos_x = new_pos_x;
		if (is_valid_position(data, player->pos_x, new_pos_y))
			player->pos_y = new_pos_y;
	}
}

/*
** Move left/right along the camera plane (strafe movement)
** Enhanced with door-aware collision detection
*/
static void	move_l_r(t_player *player, t_data *data)
{
	double	new_pos_x;
	double	new_pos_y;

	if (player->move_left)
	{
		new_pos_x = player->pos_x + player->plane_x * player->move_speed;
		new_pos_y = player->pos_y - player->plane_y * player->move_speed;
		if (is_valid_position(data, new_pos_x, player->pos_y))
			player->pos_x = new_pos_x;
		if (is_valid_position(data, player->pos_x, new_pos_y))
			player->pos_y = new_pos_y;
	}
	if (player->move_right)
	{
		new_pos_x = player->pos_x - player->plane_x * player->move_speed;
		new_pos_y = player->pos_y + player->plane_y * player->move_speed;
		if (is_valid_position(data, new_pos_x, player->pos_y))
			player->pos_x = new_pos_x;
		if (is_valid_position(data, player->pos_x, new_pos_y))
			player->pos_y = new_pos_y;
	}
}

void	move_player(t_data *data, t_player *player, char **map)
{
	(void)map;
	move_fw_bw(player, data);
	move_l_r(player, data);
	rotate_l(player);
	rotate_r(player);
}
