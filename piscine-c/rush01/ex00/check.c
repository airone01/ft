/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 12:58:00 by elagouch          #+#    #+#             */
/*   Updated: 2024/11/19 12:10:41 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rush.h"

static unsigned int count_vis(unsigned int *vals, unsigned int n) {
  unsigned int i;
  unsigned int max;
  unsigned int count;

  i = 0;
  max = 0;
  count = 0;
  while (i < n) {
    if (vals[i] > max) {
      max = vals[i];
      count++;
    }
    i++;
  }
  return (count);
}

static unsigned int check_vis(unsigned int *line, unsigned int n,
                              unsigned int hint_fwd, unsigned int hint_bwd) {
  unsigned int i;
  unsigned int rev[16];

  i = 0;
  while (i < n) {
    rev[i] = line[n - 1 - i];
    i++;
  }
  if (hint_fwd && count_vis(line, n) != hint_fwd)
    return (1);
  if (hint_bwd && count_vis(rev, n) != hint_bwd)
    return (1);
  return (0);
}

// Returns 1 if invalid, 0 if all visibility hints match and columns are unique.
unsigned int grid_check(unsigned int **grid, unsigned int size,
                        unsigned int magic) {
  unsigned int middle;
  unsigned int r;
  unsigned int c;
  unsigned int line[16];
  unsigned int seen;

  (void)magic;
  middle = size - 2;
  c = 1;
  while (c <= middle) {
    seen = 0;
    r = 1;
    while (r <= middle) {
      if (seen & (1u << grid[r][c]))
        return (1);
      seen |= 1u << grid[r][c];
      line[r - 1] = grid[r][c];
      r++;
    }
    if (check_vis(line, middle, grid[0][c], grid[size - 1][c]))
      return (1);
    c++;
  }
  r = 1;
  while (r <= middle) {
    c = 0;
    while (c < middle) {
      line[c] = grid[r][c + 1];
      c++;
    }
    if (check_vis(line, middle, grid[r][0], grid[r][size - 1]))
      return (1);
    r++;
  }
  return (0);
}
