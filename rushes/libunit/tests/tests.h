/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 15:32:30 by elagouch          #+#    #+#             */
/*   Updated: 2026/01/25 16:40:37 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TESTS_H
# define TESTS_H

# include "libunit.h"

// LAUNCHERS
int	libunit_launcher(void);

// libunit
int	test_ok(void);
int	test_ko(void);
int	test_sigsegv(void);
int	test_sigbus(void);
int	test_sigkill(void);
int	test_sigabrt(void);
int	test_sigfpe(void);
int	test_sigpipe(void);
int	test_timeout(void);

#endif // !TESTS_H
