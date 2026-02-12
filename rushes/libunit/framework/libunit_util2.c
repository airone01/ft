/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libunit_util2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 15:46:43 by elagouch          #+#    #+#             */
/*   Updated: 2026/02/12 15:02:05 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libunit.h"

/* we loop over instead of shifting the pointer to make sure we don't skip
unexisting tests and end up in unallocated/invalid memory */
t_unit_test *get_test_at(t_unit_test *head, size_t target_idx) {
  size_t j;

  j = 0;
  while ((j < target_idx) && head) {
    head = head->next;
    j++;
  }
  return (head);
}
