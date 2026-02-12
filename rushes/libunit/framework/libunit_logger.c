/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libunit_logger.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 14:26:54 by elagouch          #+#    #+#             */
/*   Updated: 2026/02/12 15:08:15 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libunit.h"
#include <stdio.h>

static void print_tabbed(int fd1, int fd2, char *s, size_t expected_len) {
  size_t i;
  size_t l;

  l = ft_strlen(s);
  ft_putstr_fd(s, fd1);
  ft_putstr_fd(s, fd2);
  i = 0;
  while (l <= expected_len && i < (expected_len - l)) {
    ft_putchar_fd(' ', fd1);
    ft_putchar_fd(' ', fd2);
    i++;
  }
}

static void print_wtermsig(int ffd, int signal) {
  static char *sigs[15];
  char *msg;

  sigs[6] = (char *)"SIGABRT";
  sigs[7] = (char *)"SIGBUS";
  sigs[8] = (char *)"SIGFPE";
  sigs[9] = (char *)"SIGKILL";
  sigs[11] = (char *)"SIGSEGV";
  sigs[13] = (char *)"SIGPIPE";
  sigs[14] = (char *)"TIMEOUT";
  ft_putstr_fd((char *)"[\x1B[33m", 1);
  ft_putstr_fd((char *)"[", ffd);
  if ((signal >= 6 && signal <= 9) || signal == 11 ||
      (signal >= 13 && signal <= 14))
    msg = sigs[signal];
  else
    msg = (char *)"UNKNOWN";
  ft_putstr_fd(msg, 1);
  ft_putstr_fd(msg, ffd);
  ft_putstr_fd((char *)"\x1B[0m]\n", 1);
  ft_putstr_fd((char *)"]\n", ffd);
}

static void interpret_status_print(const char *fn_name, int ffd,
                                   char *test_name, size_t max_len) {
  ft_putstr_fd((char *)"\x1B[94m", 1);
  ft_putstr_fd((char *)fn_name, 1);
  ft_putstr_fd((char *)fn_name, ffd);
  ft_putstr_fd((char *)"\x1B[90m : \x1B[0m", 1);
  ft_putstr_fd((char *)" : ", ffd);
  print_tabbed(1, ffd, test_name, max_len);
  ft_putstr_fd((char *)"\x1B[90m : \x1B[0m", 1);
  ft_putstr_fd((char *)": ", ffd);
}

size_t interpret_status(int ffdst[2], const char *fn_name, char *test_name,
                        size_t max_len) {
  interpret_status_print(fn_name, ffdst[0], test_name, max_len);
  if (WIFEXITED(ffdst[1])) {
    if (WEXITSTATUS(ffdst[1])) {
      ft_putstr_fd((char *)"[\x1B[31m\x1B[1mKO\x1B[0m]\n", 1);
      ft_putstr_fd((char *)"[KO]\n", ffdst[0]);
    } else {
      ft_putstr_fd((char *)"[\x1B[32mOK\x1B[0m]\n", 1);
      ft_putstr_fd((char *)"[OK]\n", ffdst[0]);
      return (1);
    }
  } else if (WIFSIGNALED(ffdst[1]))
    print_wtermsig(ffdst[0], WTERMSIG(ffdst[1]));
  return (0);
}

void print_passed_test(int ffd, size_t ok_tests, t_unit_test *test_list) {
  size_t total;

  total = count_tests(test_list);
  if (ok_tests == total)
    ft_putstr_fd((char *)"\x1B[32m", 1);
  else
    ft_putstr_fd((char *)"\x1B[31m", 1);
  ft_putnbr_fd((int)ok_tests, 1);
  ft_putnbr_fd((int)ok_tests, ffd);
  ft_putchar_fd('/', 1);
  ft_putchar_fd('/', ffd);
  ft_putnbr_fd((int)total, 1);
  ft_putnbr_fd((int)total, ffd);
  ft_putstr_fd((char *)"\x1B[0m tests passed\n\n", 1);
  ft_putstr_fd((char *)" tests passed\n\n", ffd);
}
