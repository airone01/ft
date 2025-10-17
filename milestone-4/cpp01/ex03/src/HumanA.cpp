/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanA.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 17:33:45 by elagouch          #+#    #+#             */
/*   Updated: 2025/08/26 16:56:18 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HumanA.hpp"
#include <iostream>
#include <ostream>

// Default constructor
HumanA::HumanA() : _name("Bruce"), _weapon("machine gun") {};
// Copy constructor
HumanA::HumanA(const HumanA &other)
    : _name(other._name), _weapon(other._weapon) {}
// Parameterized constructor
HumanA::HumanA(const std::string &name, const Weapon &weapon)
    : _name(name), _weapon(weapon) {}

// Destructor
HumanA::~HumanA() {}

// Copy asignment operator
HumanA &HumanA::operator=(const HumanA &other) {
  if (this != &other) {
    _name = other._name;
    _weapon = other._weapon;
  }
  return *this;
}

// Methods
void HumanA::attack() {
  std::cout << _name << " attacks with their " << _weapon.getType()
            << std::endl;
};
