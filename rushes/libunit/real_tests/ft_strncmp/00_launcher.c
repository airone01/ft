/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_launcher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgaillet <dgaillet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 12:05:05 by dgaillet          #+#    #+#             */
/*   Updated: 2026/02/12 15:12:23 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../tests.h"

int strncmp_launcher(void) {
  t_unit_test *testlist;
  int res;

  testlist = NULL;
  load_test(&testlist, "Basic test", &strncmp_basic_test, 0);
  load_test(&testlist, "Len test", &strncmp_len_test, 0);
  load_test(&testlist, "High len test", &strncmp_high_len_test, 0);
  res = launch_tests(testlist, "ft_strncmp");
  clear_tests(&testlist);
  return (res);
}
