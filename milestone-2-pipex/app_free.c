/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 16:12:57 by elagouch          #+#    #+#             */
/*   Updated: 2025/01/30 16:16:00 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/**
 * @brief	Frees the whole app structure
 */
void	app_free(t_app app)
{
	free_fds(app);
	ft_lstclear(&app.cmds, nothing);
	ft_lstclear(&app.cmdas, (void (*)(void *))free_strings);
}
