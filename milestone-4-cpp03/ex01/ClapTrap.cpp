/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClapTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 12:28:00 by elagouch          #+#    #+#             */
/*   Updated: 2025/08/27 15:49:57 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClapTrap.hpp"
#include <iostream>
#include <ostream>

// Default contructor
ClapTrap::ClapTrap()
    : _name("David Eddings"), _hitPoints(10), _energyPoints(10),
      _attackDamage(0) {
  std::cout << "ClapTrap " << _name << " was created! (default constructor)"
            << std::endl;
};
// Parameterized constructor
ClapTrap::ClapTrap(const std::string &name)
    : _name(name), _hitPoints(10), _energyPoints(10), _attackDamage(0) {
  std::cout << "ClapTrap " << _name << " was created! (named constructor)"
            << std::endl;
}
// Copy constructor
ClapTrap::ClapTrap(const ClapTrap &other)
    : _name(other._name), _hitPoints(other._hitPoints),
      _energyPoints(other._energyPoints), _attackDamage(other._attackDamage) {
  std::cout << "ClapTrap " << _name << " was created! (copy constructor)"
            << std::endl;
}
// Destructor
ClapTrap::~ClapTrap() {
  std::cout << "ClapTrap " << _name << " is destroyed!" << std::endl;
}

// Copy assignment operator
ClapTrap &ClapTrap::operator=(const ClapTrap &other) {
  if (this != &other) {
    _name = other._name;
    _hitPoints = other._hitPoints;
    _energyPoints = other._energyPoints;
    _attackDamage = other._attackDamage;
  }
  return *this;
}

// Public methods
void ClapTrap::attack(const std::string &target) {
  if (_energyPoints > 0) {
    _energyPoints--;
    std::cout << "ClapTrap " << _name << " attacks " << target << " (-"
              << _attackDamage << " DMG)." << std::endl;
  } else {
    std::cout << "ClapTrap " << _name << " tries to attack but is out of EP!"
              << std::endl;
  }
}
void ClapTrap::takeDamage(unsigned int damage) {
  std::cout << "ClapTrap " << _name << " takes " << damage << " DMG (-"
            << _hitPoints << " -> " << _hitPoints - damage << " HP)."
            << std::endl;
  if (_hitPoints - damage < 0)
    _hitPoints = 0;
  else
    _hitPoints -= damage;
}
void ClapTrap::beRepaired(unsigned int repaired) {
  if (_energyPoints > 0) {
    _energyPoints--;
    _hitPoints += repaired;
    if (_hitPoints > 10)
      _hitPoints = 10;
    std::cout << "ClapTrap " << _name << " repairs itself (+" << repaired
              << " -> " << _hitPoints << " HP)." << std::endl;
  } else {
    std::cout << "ClapTrap " << _name
              << " tries to repair itself but is out of EP!" << std::endl;
  }
}
