/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Weapon.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 17:22:21 by elagouch          #+#    #+#             */
/*   Updated: 2026/01/12 17:34:16 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Weapon.hpp"

// Default constructor
Weapon::Weapon() : _type("lightsaber") {}
// Copy constructor
Weapon::Weapon(const Weapon &other) : _type(other._type) {}
// Parameterized import
Weapon::Weapon(const std::string &type) : _type(type) {}

// Destructor
Weapon::~Weapon() {}

// Getters
std::string &Weapon::getType(void) { return _type; }

// Setters
void Weapon::setType(const std::string &newType) { _type = newType; }
