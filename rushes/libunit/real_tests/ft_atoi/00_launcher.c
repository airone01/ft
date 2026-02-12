/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_launcher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgaillet <dgaillet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 16:22:35 by dgaillet          #+#    #+#             */
/*   Updated: 2026/02/12 15:11:53 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../tests.h"

int atoi_launcher(void) {
  t_unit_test *testlist;
  int res;

  testlist = NULL;
  load_test(&testlist, "Basic test", &atoi_basic_test, 0);
  load_test(&testlist, "INT MAX test", &atoi_int_max_test, 0);
  load_test(&testlist, "INT MIN test", &atoi_int_min_test, 0);
  load_test(&testlist, "NULL test", &atoi_null_test, 0);
  res = launch_tests(testlist, "atoi");
  clear_tests(&testlist);
  return (res);
}
