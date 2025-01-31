/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 16:12:57 by elagouch          #+#    #+#             */
/*   Updated: 2025/01/31 16:14:43 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/**
 * @brief	Frees the whole app structure
 */
void	app_free(t_app app)
{
	if (app.bonus_pipes[0] != -1)
		close(app.bonus_pipes[0]);
	if (app.bonus_pipes[1] != -1)
		close(app.bonus_pipes[1]);
	ft_lstclear(&app.cmdas, (void (*)(void *))free_strings);
}
