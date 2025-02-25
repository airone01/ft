/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_render_lod.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 09:10:27 by elagouch          #+#    #+#             */
/*   Updated: 2025/02/25 13:49:13 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/**
 * @brief Displays numeric LOD debug info using mlx_string_put
 *
 * @param ctx Application context
 * @param value Numeric value to display
 * @param label Label text
 * @param y_pos Vertical position for the text
 */
void	put_debug_number(t_app *ctx, double value, char *label, int y_pos)
{
	char	num_str[16];
	char	full_str[64];
	int		i;
	int		decimal_part;
	int		whole_part;

	whole_part = (int)value;
	decimal_part = (int)((value - whole_part) * 100);
	if (decimal_part < 0)
		decimal_part = -decimal_part;
	ft_strlcpy(num_str, ft_itoa(whole_part), 16);
	ft_strlcat(num_str, (char *)".", 16);
	if (decimal_part < 10)
		ft_strlcat(num_str, (char *)"0", 16);
	ft_strlcat(num_str, ft_itoa(decimal_part), 16);
	i = 0;
	while (i < 64)
	{
		full_str[i] = '\0';
		i++;
	}
	ft_strlcpy(full_str, label, 64);
	ft_strlcat(full_str, num_str, 64);
	mlx_string_put(ctx->mlx, ctx->win, 10, y_pos, 0x00FFFFFF, full_str);
}
