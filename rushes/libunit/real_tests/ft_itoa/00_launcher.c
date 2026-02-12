/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_launcher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgaillet <dgaillet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 17:12:06 by dgaillet          #+#    #+#             */
/*   Updated: 2026/02/12 15:12:02 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../tests.h"

int itoa_launcher(void) {
  t_unit_test *testlist;
  int res;

  testlist = NULL;
  load_test(&testlist, "Positif test", &itoa_positif_test, 0);
  load_test(&testlist, "Negatif test", &itoa_negatif_test, 0);
  load_test(&testlist, "Zero test", &itoa_zero_test, 0);
  load_test(&testlist, "INT MAX test", &itoa_int_max_test, 0);
  load_test(&testlist, "INT MIN test", &itoa_int_max_test, 0);
  res = launch_tests(testlist, "itoa");
  clear_tests(&testlist);
  return (res);
}
