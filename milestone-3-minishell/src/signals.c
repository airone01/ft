/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 17:58:55 by elagouch          #+#    #+#             */
/*   Updated: 2025/05/06 18:21:26 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "globals.h"
#include "minishell.h" // required bc globals.h does not include minishell.h

/*
For best signals, see:
- 1fd7c87
- b910dfc
*/

/////////////////////////////// Interactive mode ///////////////////////////////

/**
 * @brief Signal handler for interactive mode
 *
 * @param sig Signal number received
 */
void	sig_interactive_handler(int sig)
{
	if (sig == SIGINT)
	{
		g_signal_status = 130;
		write(STDOUT_FILENO, "^C\n", 3);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

/**
 * @brief Sets up signal handlers for interactive mode
 * SIGINT (CTRL+C) is handled for status update
 * SIGQUIT (CTRL+\) is ignored
 */
void	setup_interactive_signals(void)
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;

	rl_catch_signals = 0;
	rl_catch_sigwinch = 1;
	sigemptyset(&sa_int.sa_mask);
	sigemptyset(&sa_quit.sa_mask);
	sa_int.sa_flags = SA_RESTART;
	sa_quit.sa_flags = 0;
	sa_int.sa_handler = sig_interactive_handler;
	sa_quit.sa_handler = SIG_IGN;
	sigaction(SIGINT, &sa_int, NULL);
	sigaction(SIGQUIT, &sa_quit, NULL);
	g_signal_status = 0;
}

//////////////////////////////////// Parent ////////////////////////////////////
///////////////////////////////// During exec //////////////////////////////////

/**
 * @brief Sets up signal handlers for parent process during command execution
 * Ignores signals to preserve nested shell behavior
 */
void	setup_parent_signals(void)
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;

	g_signal_status = 0;
	sigemptyset(&sa_int.sa_mask);
	sigemptyset(&sa_quit.sa_mask);
	sa_int.sa_flags = 0;
	sa_quit.sa_flags = 0;
	sa_int.sa_handler = SIG_IGN;
	sa_quit.sa_handler = SIG_IGN;
	sigaction(SIGINT, &sa_int, NULL);
	sigaction(SIGQUIT, &sa_quit, NULL);
}

//////////////////////////////////// Child /////////////////////////////////////
///////////////////////////////// During exec //////////////////////////////////

/**
 * @brief Resets signal handlers for child processes during command execution
 * SIGINT and SIGQUIT are set to their default behavior
 */
void	setup_child_signals(void)
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;

	g_signal_status = 0;
	sigemptyset(&sa_int.sa_mask);
	sigemptyset(&sa_quit.sa_mask);
	sa_int.sa_flags = 0;
	sa_quit.sa_flags = 0;
	sa_int.sa_handler = SIG_DFL;
	sa_quit.sa_handler = SIG_DFL;
	sigaction(SIGINT, &sa_int, NULL);
	sigaction(SIGQUIT, &sa_quit, NULL);
}

// Other stuff

/**
 * @brief Updates context exit status based on signal status
 *
 * @param ctx Context to update
 */
void	update_signal_status(t_ctx *ctx)
{
	if (g_signal_status != 0)
	{
		ctx->exit_status = g_signal_status;
		g_signal_status = 0;
	}
}
