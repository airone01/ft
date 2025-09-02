/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanB.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 17:33:45 by elagouch          #+#    #+#             */
/*   Updated: 2025/08/26 16:56:12 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HumanB.hpp"
#include <cstddef>
#include <iostream>

// Default constructor
HumanB::HumanB() : _name("Jackie"), _weapon(NULL) {}
// Copy constructor
HumanB::HumanB(const HumanB &other)
    : _name(other._name), _weapon(other._weapon) {}
// Parameterized constructor (no weapon)
HumanB::HumanB(const std::string &name) : _name(name), _weapon(NULL) {}

// Destructor
HumanB::~HumanB() {
  if (_weapon)
    delete _weapon;
}

// Copy asignment operator
HumanB &HumanB::operator=(const HumanB &other) {
  if (this != &other) {
    _name = other._name;
    _weapon = other._weapon;
  }
  return *this;
}

// Setters
void HumanB::setWeapon(Weapon &weapon) { _weapon = &weapon; }

// Methods
void HumanB::attack() {
  Weapon *wp = _weapon;
  if (wp)
    std::cout << _name << " attacks with their " << wp->getType() << std::endl;
  else
    std::cout << _name << " attacks without a weapon!" << std::endl;
}
