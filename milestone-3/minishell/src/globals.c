/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   globals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 13:24:12 by elagouch          #+#    #+#             */
/*   Updated: 2025/05/06 15:10:12 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "globals.h"

// int	g_signal_status = 0;

/*
Because of an obscure bug with `ld`, we need this file as well as the
associated header `globals.h`. Otherwise having functions defined not in the
same exact file can break minishell signals (???), which is obviously not
possible because of the norm.
*/
