/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FragTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 13:38:55 by elagouch          #+#    #+#             */
/*   Updated: 2025/08/27 16:15:23 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FragTrap.hpp"
#include <iostream>
#include <ostream>

/*
 * Note: we cannot re-use the ClapTrap constructors because they display their
 * own message
 */

// Default contructor
FragTrap::FragTrap() : ClapTrap("INAC") {
  _hitPoints = 100;
  _energyPoints = 100;
  _attackDamage = 30;
  std::cout << "FragTrap " << _name
            << " was created from a ClapTrap! (default constructor)"
            << std::endl;
};
// Parameterized constructor
FragTrap::FragTrap(const std::string &name) : ClapTrap(name) {
  _hitPoints = 100;
  _energyPoints = 100;
  _attackDamage = 30;
  std::cout << "FragTrap " << _name
            << " was created from a ClapTrap! (named constructor)" << std::endl;
}
// Copy constructor
FragTrap::FragTrap(const FragTrap &other) : ClapTrap(other) {
  std::cout << "FragTrap " << _name
            << " was created from a ClapTrap! (copy constructor)" << std::endl;
}
// Destructor
FragTrap::~FragTrap() {
  std::cout << "FragTrap " << _name << " is destroyed!" << std::endl;
}

FragTrap &FragTrap::operator=(const FragTrap &other) {
  if (this != &other) {
    _name = other._name;
    _hitPoints = other._hitPoints;
    _energyPoints = other._energyPoints;
    _attackDamage = other._attackDamage;
  }
  return *this;
}

// Public methods
void FragTrap::highFivesGuys(void) {
  std::cout << "FragTrap " << _name << " says \"Hey, slave, high five me!\""
            << std::endl;
}
void FragTrap::attack(const std::string &target) {
  if (_energyPoints > 0) {
    _energyPoints--;
    std::cout << "FragTrap " << _name << " attacks " << target << " (-"
              << _attackDamage << " DMG)." << std::endl;
  } else {
    std::cout << "FragTrap " << _name << " tries to attack but is out of EP!"
              << std::endl;
  }
}
