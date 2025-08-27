/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScavTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 13:38:55 by elagouch          #+#    #+#             */
/*   Updated: 2025/08/27 15:51:42 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScavTrap.hpp"
#include <iostream>
#include <ostream>

/*
 * Note: we cannot re-use the ClapTrap constructors because they display their
 * own message
 */

// Default contructor
ScavTrap::ScavTrap() : ClapTrap("SC4V-TP") {
  _hitPoints = 100;
  _energyPoints = 50;
  _attackDamage = 20;
  std::cout << "ScavTrap " << _name << " was created from a ClapTrap! (default constructor)"
            << std::endl;
};
// Parameterized constructor
ScavTrap::ScavTrap(const std::string &name) : ClapTrap(name) {
  _hitPoints = 100;
  _energyPoints = 50;
  _attackDamage = 20;
  std::cout << "ScavTrap " << _name << " was created from a ClapTrap! (named constructor)"
            << std::endl;
}
// Copy constructor
ScavTrap::ScavTrap(const ScavTrap &other) : ClapTrap(other) {
  std::cout << "ScavTrap " << _name << " was created from a ClapTrap! (copy constructor)"
            << std::endl;
}
// Destructor
ScavTrap::~ScavTrap() {
  std::cout << "ScavTrap " << _name << " is destroyed!" << std::endl;
}

// Public methods
void ScavTrap::guardGate(void) {
  std::cout << "ScavTrap" << _name << " is now in Gate keeper mode." << std::endl;
}
