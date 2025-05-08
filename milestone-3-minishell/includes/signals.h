/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 13:28:53 by elagouch          #+#    #+#             */
/*   Updated: 2025/05/06 17:56:38 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

# include "minishell.h"

// *************************************************************************** #
//                            Function Prototypes                              #
// *************************************************************************** #

// signals.c
void	setup_interactive_signals(void);
void	setup_child_signals(void);
void	setup_parent_signals(void);
void	setup_heredoc_signals(void);

// signals_update.c
void	update_signal_status(t_ctx *ctx);

#endif
