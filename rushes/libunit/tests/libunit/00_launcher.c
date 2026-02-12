/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_launcher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 15:32:32 by elagouch          #+#    #+#             */
/*   Updated: 2026/02/12 15:01:09 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../tests.h"

int libunit_launcher(void) {
  t_unit_test *testlist;
  int res;

  testlist = NULL;
  load_test(&testlist, "successful", &test_ok, 0);
  load_test(&testlist, "unsuccessful", &test_ko, 0);
  load_test(&testlist, "sigsegv", &test_sigsegv, 0);
  load_test(&testlist, "sigbus", &test_sigbus, 0);
  load_test(&testlist, "sigkill", &test_sigkill, 0);
  load_test(&testlist, "sigabrt", &test_sigabrt, 0);
  load_test(&testlist, "sigfpe", &test_sigfpe, 0);
  load_test(&testlist, "sigpipe", &test_sigpipe, 0);
  load_test(&testlist, "timeout", &test_timeout, 1);
  res = launch_tests(testlist, "libunit");
  clear_tests(&testlist);
  return (res);
}
