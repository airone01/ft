/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_launcher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgaillet <dgaillet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 16:56:28 by dgaillet          #+#    #+#             */
/*   Updated: 2026/02/12 15:12:09 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../tests.h"

int strdup_launcher(void) {
  t_unit_test *testlist;
  int res;

  testlist = NULL;
  load_test(&testlist, "Basic test", &strdup_basic_test, 0);
  load_test(&testlist, "Basic test", &strdup_null_test, 0);
  res = launch_tests(testlist, "strdup");
  clear_tests(&testlist);
  return (res);
}
