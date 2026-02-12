/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libunit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgaillet <dgaillet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 12:43:35 by dgaillet          #+#    #+#             */
/*   Updated: 2026/02/12 15:09:40 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libunit.h"
#include <fcntl.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

static int parent_helper(int ffd, struct s_helper *h, const char *fn_name,
                         t_unit_test *test_list) {
  int status;
  int ffdst[2];
  pid_t caught_pid;

  caught_pid = 0;
  while (caught_pid != h->wpid) {
    caught_pid = wait(&status);
    if (caught_pid < 0)
      return (-1);
  }
  ffdst[0] = ffd;
  ffdst[1] = status;
  h->ok_tests += interpret_status(ffdst, fn_name,
                                  get_test_at(test_list, (size_t)h->i)->title,
                                  test_list->max_len);
  return (0);
}

static int child_helper(t_unit_test *test_list, t_h h, int ffd) {
  int fd;
  int res;
  t_unit_test *test;

  fd = open("/dev/null", O_WRONLY);
  if (!fd)
    return (-1);
  if (dup2(fd, STDOUT_FILENO) < 0)
    return (-1);
  test = get_test_at(test_list, (size_t)h.i);
  if (test->timeout)
    alarm(test->timeout);
  res = test->func();
  close(fd);
  close(ffd);
  clear_tests(&test_list);
  exit(res);
}

static int handle_out(const char *fn_name) {
  char *tmp;
  int fd;

  tmp = ft_strjoin(fn_name, ".log");
  if (!tmp)
    return (-1);
  fd = open(tmp, O_WRONLY | O_CREAT | O_TRUNC, 0644);
  free(tmp);
  return (fd);
}

int launch_tests(t_unit_test *test_list, const char *fn_name) {
  int ffd;
  t_h h;

  h.ok_tests = 0;
  h.i = -1;
  ffd = handle_out(fn_name);
  if (ffd < 0)
    return (-1);
  while (++h.i < (int)count_tests(test_list)) {
    h.wpid = fork();
    if (h.wpid < 0)
      return (-1);
    else if (h.wpid == 0 && child_helper(test_list, h, ffd) < 0)
      return (-1);
    else if (parent_helper(ffd, &h, fn_name, test_list))
      return (-1);
  }
  print_passed_test(ffd, h.ok_tests, test_list);
  close(ffd);
  if (h.ok_tests != count_tests(test_list))
    return (-1);
  return (0);
}
