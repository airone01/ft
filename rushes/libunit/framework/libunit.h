/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libunit.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 14:38:40 by elagouch          #+#    #+#             */
/*   Updated: 2026/02/12 15:07:05 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBUNIT_H
#define LIBUNIT_H

#include "libft.h"
#include <sys/types.h>
#include <unistd.h>

/**
 * @brief singular unit test def
 */
typedef struct s_unit_test {
  char *title;
  int (*func)(void);
  struct s_unit_test *next;
  unsigned int timeout;
  size_t max_len;
} t_unit_test;

/**
 * @brief finds a test at index
 *
 * @return test or NULL
 */
t_unit_test *get_test_at(t_unit_test *head, size_t target_idx);

/**
 * @brief count tests
 *
 * @return size_t test count
 */
size_t count_tests(t_unit_test *head);

/**
 * @brief adds a new test
 * @brief alternatively, if the passed head is empty, replace it with the
 * initial test
 *
 * @param head_ptr pointer to the head of the tests list
 * @param title name of the test
 * @param test_func function to execute the test
 *
 * @return -1 on error, 0 on success
 */
ssize_t load_test(t_unit_test **head_ptr, const char *title,
                  int (*test_func)(void), unsigned int timeout);

/**
 * @brief clears the tests memory
 */
void clear_tests(t_unit_test **head_ptr);

/**
 * @brief launches the tests and returns the reported status
 */
int launch_tests(t_unit_test *test_list, const char *fn_name);

typedef struct s_helper {
  pid_t wpid;
  size_t ok_tests;
  int i;
} t_h;

size_t interpret_status(int ffdst[2], const char *fn_name, char *test_name,
                        size_t spaces);

void print_passed_test(int ffd, size_t ok_tests, t_unit_test *test_list);

#endif // !LIBUNIT_H
