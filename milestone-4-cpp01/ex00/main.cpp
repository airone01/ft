/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 12:37:49 by elagouch          #+#    #+#             */
/*   Updated: 2025/08/21 16:23:57 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

int main() {
  randomChump("Gedagedigedagedago");
  Zombie *zomb = newZombie("Gedagedigedagedago2");
  zomb->announce();
  delete zomb;
}
