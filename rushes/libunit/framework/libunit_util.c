/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libunit_util.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 14:35:57 by elagouch          #+#    #+#             */
/*   Updated: 2026/02/12 15:07:11 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libunit.h"
#include <stdlib.h>

size_t count_tests(t_unit_test *head) {
  size_t j;

  j = 0;
  while (head) {
    head = head->next;
    j++;
  }
  return (j);
}

/**
 * @brief util function to get last test of the chain
 */
t_unit_test *get_last(t_unit_test *head) {
  while (head->next)
    head = head->next;
  return (head);
}

/**
 * @brief util function to allocate a new test
 */
static t_unit_test *alloc_test(const char *title, int (*test_func)(void),
                               unsigned int timeout) {
  t_unit_test *p;

  p = malloc(sizeof(t_unit_test));
  p->title = ft_strdup(title);
  p->func = test_func;
  p->next = NULL;
  p->timeout = timeout;
  p->max_len = 0;
  return (p);
}

ssize_t load_test(t_unit_test **head_ptr, const char *title,
                  int (*test_func)(void), unsigned int timeout) {
  t_unit_test *last;
  size_t tlen;

  if (!head_ptr)
    return (-1);
  tlen = ft_strlen(title);
  if (!*head_ptr) {
    *head_ptr = alloc_test(title, test_func, timeout);
    if (!*head_ptr)
      return (-1);
    (*head_ptr)->max_len = ft_strlen(title);
    return (0);
  }
  last = get_last(*head_ptr);
  last->next = alloc_test(title, test_func, timeout);
  if (!last->next)
    return (-1);
  if ((*head_ptr)->max_len < tlen)
    (*head_ptr)->max_len = tlen;
  return (0);
}

void clear_tests(t_unit_test **head_ptr) {
  t_unit_test *current;
  t_unit_test *next;

  if (!head_ptr)
    return;
  current = *head_ptr;
  while (current) {
    next = current->next;
    if (current->title)
      free(current->title);
    free(current);
    current = next;
  }
  *head_ptr = NULL;
}
