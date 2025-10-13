/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zombieHorde.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 16:28:12 by elagouch          #+#    #+#             */
/*   Updated: 2025/08/21 16:51:09 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"
#include <cstddef>

Zombie *zombieHorde(int N, std::string name) {
  if (N <= 0)
    return NULL;
  Zombie *zombs = new Zombie[N];
  for (int i=0; i<N; i++) {
    zombs[i].setName(name);
  }
  return (zombs);
}
