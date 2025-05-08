/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 13:59:38 by elagouch          #+#    #+#             */
/*   Updated: 2025/05/08 17:05:01 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "globals.h"
#include "minishell.h" // required bc globals.h does not include minishell.h

/**
 * @brief Displays a warning message when heredoc is terminated by EOF
 *
 * This function prints a formatted warning message to stderr when
 * the user terminates a heredoc with Ctrl+D instead of typing the delimiter.
 */
static void	display_heredoc_eof_warning(void)
{
	char	*warning_part1;
	char	*warning_part2;
	char	*warning_part3;

	warning_part1 = (char *)"minishell: warning: heredoc: ";
	warning_part2 = (char *)"here-document delimited by end-of-file ";
	warning_part3 = (char *)"(`eof')\n";
	ft_printf_fd(STDERR_FILENO, YELLOW "%s%s%s" RESET, warning_part1,
		warning_part2, warning_part3);
}

/**
 * Reads a line from standard input for heredoc
 *
 * This function reads a line of input for a heredoc and checks if it matches
 * the delimiter or if the user has pressed Ctrl+D. It returns different values
 * depending on the result.
 *
 * @param delimiter The heredoc delimiter string
 * @param line Pointer to store the read line
 * @return 1 if delimiter matched or EOF encountered, 0 if normal line, -1 on
 * error
 */
int	read_heredoc_line(char *delimiter, char **line)
{
	int	delimiter_len;

	if (g_signal_status == 130)
		return (-1);
	delimiter_len = (int)ft_strlen(delimiter);
	rl_catch_signals = 0;
	rl_catch_sigwinch = 0;
	*line = readline("> ");
	if (!(*line) || g_signal_status == 130)
	{
		if (*line && g_signal_status == 130)
		{
			free(*line);
			*line = NULL;
		}
		else if (!(*line))
			return (display_heredoc_eof_warning(), 1);
		return (-1);
	}
	if (ft_strncmp(*line, delimiter, (unsigned long)delimiter_len + 1) == 0)
	{
		free(*line);
		return (1);
	}
	return (0);
}

/**
 * Sets up heredoc pipe and prepares for content reading
 *
 * This function creates a pipe for heredoc content and returns status code.
 *
 * @param pipe_fds Array to store pipe file descriptors
 * @return 0 on success, -1 on error
 */
int	setup_heredoc_pipes(int pipe_fds[2])
{
	if (pipe(pipe_fds) == -1)
	{
		perror("minishell: pipe setup failed");
		return (-1);
	}
	return (0);
}

/**
 * Waits for heredoc child process to complete
 *
 * This function waits for the heredoc child process and handles errors.
 *
 * @param pipe_fds Array of pipe file descriptors
 * @param ctx Shell context
 * @return Read end of pipe on success, -1 on error
 */
int	wait_heredoc_child(int pipe_fds[2], t_ctx *ctx)
{
	int	status;
	int	exit_code;
	int	read_fd;

	read_fd = pipe_fds[0];
	waitpid(-1, &status, 0);
	if (WIFEXITED(status))
	{
		exit_code = WEXITSTATUS(status);
		if (exit_code != 0)
		{
			close(read_fd);
			ctx->exit_status = exit_code;
			return (-1);
		}
	}
	else if (WIFSIGNALED(status))
	{
		close(read_fd);
		ctx->exit_status = 130;
		return (-1);
	}
	return (read_fd);
}
