/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 18:10:00 by elagouch          #+#    #+#             */
/*   Updated: 2025/05/07 11:44:38 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"
#include "commands.h"
#include "execute.h"
#include "free.h"
#include "init.h"
#include "lexer.h"
#include "signals.h"
#include "validation.h"

/**
 * @brief Processes user input and executes commands
 *
 * Handles tokenization, parsing, and execution of user input
 *
 * @param ctx Shell context
 * @param input User input string
 */
static void	process_user_input(t_ctx *ctx, char *input)
{
	ctx->tokens = tokenize(ctx, input);
	if (ctx->tokens && validate_token_sequence(ctx->tokens))
	{
		ctx->cmd = command_parse(ctx, ctx->tokens);
		if (ctx->cmd)
			execute_commands(ctx, ctx->cmd);
	}
	else
		ctx->exit_status = 2;
}

/**
 * @brief Cleans up resources after command execution
 *
 * Frees tokens and commands, updates signal status
 *
 * @param ctx Shell context
 */
static void	cleanup_resources(t_ctx *ctx)
{
	if (ctx->tokens)
	{
		free_all_token(ctx->tokens);
		ctx->tokens = NULL;
	}
	if (ctx->cmd)
	{
		free_all_commands(ctx->cmd);
		ctx->cmd = NULL;
	}
	update_signal_status(ctx);
}

/**
 * @brief Main command loop for the shell
 *
 * Reads user input, processes commands in a loop,
 * and manages the shell's main control flow
 *
 * @param ctx Shell context
 * @return int Final exit status
 */
static int	command_loop(t_ctx *ctx)
{
	char	*input;

	while (!ctx->exit_requested)
	{
		setup_interactive_signals();
		input = readline("$ ");
		if (!input)
		{
			ft_printf("exit\n");
			break ;
		}
		update_signal_status(ctx);
		if (*input)
			add_history(input);
		if (validate_input_length(input, ctx))
			process_user_input(ctx, input);
		cleanup_resources(ctx);
		free(input);
	}
	return (ctx->exit_status);
}

/**
 * @brief Main entrypoint for the minishell program
 *
 * Initializes context, sets up signals, runs command loop
 *
 * @param argc Argument count
 * @param argv Argument values
 * @param envp Environment variables array
 * @return int Exit status
 */
int	main(int argc, char **argv, char **envp)
{
	t_ctx	*ctx;
	int		final_status;

	if (!isatty(STDOUT_FILENO) || !isatty(STDIN_FILENO))
	{
		ft_printf_fd(2, "not a tty\n");
		exit(EXIT_FAILURE);
	}
	ctx = init_ctx(argc, argv, envp);
	setup_interactive_signals();
	final_status = command_loop(ctx);
	ctx_clear(ctx);
	return (final_status);
}
