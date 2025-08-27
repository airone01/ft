/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 12:41:15 by elagouch          #+#    #+#             */
/*   Updated: 2025/08/27 12:56:57 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClapTrap.hpp"

int main(void) {
  ClapTrap bob("Bob");
  bob.attack("Handsome Jack");
  bob.takeDamage(5);
  bob.takeDamage(1);
  bob.beRepaired(2);
  bob.beRepaired(3);
  bob.attack("Handsome Jack");
  bob.attack("Handsome Jack");
  bob.attack("Handsome Jack");
  bob.attack("Handsome Jack");
  bob.attack("Handsome Jack");
  bob.attack("Handsome Jack");
  bob.attack("Handsome Jack");
  bob.attack("Handsome Jack");
}
