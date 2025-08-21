/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 12:37:49 by elagouch          #+#    #+#             */
/*   Updated: 2025/08/20 12:58:39 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

Zombie *newZombie(std::string name) {
  Zombie* zomb = new Zombie(name);
  return (zomb);
}

void randomChump(std::string name) {
  Zombie zomb(name);
  zomb.announce();
}

int main() {
  randomChump("Gedagedigedagedago");
  Zombie *zomb = newZombie("Gedagedigedagedago2");
  zomb->announce();
  delete zomb;
}
