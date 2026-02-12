/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 15:32:30 by elagouch          #+#    #+#             */
/*   Updated: 2026/01/24 18:40:48 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TESTS_H
# define TESTS_H

# include "libunit.h"

// LAUNCHERS
int	strlen_launcher(void);
int	atoi_launcher(void);
int	strncmp_launcher(void);
int	strdup_launcher(void);
int	itoa_launcher(void);

// strlen
int	test_basic(void);
int	test_null(void);
int	test_large(void);

// atoi
int	atoi_basic_test(void);
int	atoi_int_max_test(void);
int	atoi_int_min_test(void);
int	atoi_null_test(void);

// strncmp
int	strncmp_basic_test(void);
int	strncmp_len_test(void);
int	strncmp_high_len_test(void);

//strdup
int	strdup_basic_test(void);
int	strdup_null_test(void);

//itao
int	itoa_positif_test(void);
int	itoa_negatif_test(void);
int	itoa_zero_test(void);
int	itoa_int_max_test(void);
int	itoa_int_min_test(void);

#endif // !TESTS_H
