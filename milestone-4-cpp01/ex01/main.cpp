/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 16:21:31 by elagouch          #+#    #+#             */
/*   Updated: 2025/08/21 16:59:11 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

int main (void) {
  int N = 7;
  Zombie *zombs = zombieHorde(N, "Ed");
  for (int i=0; i<N; i++) {
    zombs[i].announce();
  }
  delete[] zombs;
}
