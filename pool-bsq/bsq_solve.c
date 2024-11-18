/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsq_solve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macombe <macombe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 18:15:31 by macombe           #+#    #+#             */
/*   Updated: 2024/10/02 20:04:31 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "h_main.h"

static int	min(int a, int b, int c)
{
	if (a <= b && a <= c)
		return (a);
	if (b <= a && b <= c)
		return (b);
	return (c);
}

void	idk_anymore(int ijmm[4], t_map map, int *curr, int *max_size)
{
	int	dp[2][1000];

	while (ijmm[0] < map.coords.y)
	{
		ijmm[1] = 0;
		while (ijmm[1] < map.coords.x)
		{
			if (map.map[ijmm[0]][ijmm[1]] == '0')
				dp[*curr][ijmm[1]] = 0;
			else if (ijmm[0] == 0 || ijmm[1] == 0)
				dp[*curr][ijmm[1]] = 1;
			else
				dp[*curr][ijmm[1]] = min(dp[1 - *curr][ijmm[1]],
						dp[*curr][ijmm[1] - 1], dp[1 - *curr][ijmm[1] - 1]) + 1;
			if (dp[*curr][ijmm[1]] > *max_size)
			{
				*max_size = dp[*curr][ijmm[1]];
				ijmm[2] = ijmm[0];
				ijmm[3] = ijmm[1];
			}
			ijmm[1]++;
		}
		*curr = 1 - *curr;
		ijmm[0]++;
	}
}

void	bsq_solve(t_map map)
{
	int	max_size;
	int	ijmm[4];
	int	curr;

	max_size = 0;
	ijmm[0] = 0;
	ijmm[2] = 0;
	ijmm[3] = 0;
	curr = 0;
	idk_anymore(ijmm, map, &curr, &max_size);
	ijmm[0] = ijmm[2];
	while (ijmm[0] > ijmm[2] - max_size)
	{
		ijmm[1] = ijmm[3];
		while (ijmm[1] > ijmm[3] - max_size)
		{
			map.map[ijmm[0]][ijmm[1]] = full;
			ijmm[1]--;
		}
		ijmm[0]--;
	}
}
