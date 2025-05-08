/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 16:57:36 by maximart          #+#    #+#             */
/*   Updated: 2025/05/06 13:34:17 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Displays an error message to STDERR
 *
 * @param proof (optional) Proof that the error occured
 * @param module (optional) Module where the error occured
 * @param msg Error message
 */
void	error_print(const char *proof, const char *module, const char *msg)
{
	ft_printf_fd(STDERR_FILENO, "minishell: ");
	if (module && proof)
		ft_printf_fd(STDERR_FILENO, "%s: %s: %s\n", module, proof, msg);
	else if (module)
		ft_printf_fd(STDERR_FILENO, "%s: %s\n", module, msg);
	else if (proof)
		ft_printf_fd(STDERR_FILENO, "%s: %s\n", proof, msg);
	else
		ft_printf_fd(STDERR_FILENO, "%s\n", msg);
}
