/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@42>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 10:16:09 by elagouch          #+#    #+#             */
/*   Updated: 2024/10/01 10:26:42 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "h_main.h"

/*
 * Puts a string to stdout.
 */
void	ft_putchar(char c)
{
	write(1, &c, 1);
}

/*
 * Puts a string to stdout.
 */
void	ft_putstr(char *str)
{
	write(1, str, ft_strlen(str));
}

/*
 * Puts a string to stderr.
 */
void	ft_puterr(char *str)
{
	write(2, str, ft_strlen(str));
}
