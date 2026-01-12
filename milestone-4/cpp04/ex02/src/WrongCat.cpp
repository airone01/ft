/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WrongCat.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 18:30:00 by elagouch          #+#    #+#             */
/*   Updated: 2026/01/12 17:32:25 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "WrongCat.hpp"
#include <iostream>
#include <ostream>

// Default constructor
WrongCat::WrongCat(void) : WrongAnimal("WrongCat") {}
// Copy constructor
WrongCat::WrongCat(const WrongCat &other) : WrongAnimal(other) {}
// Destructor
WrongCat::~WrongCat(void) {}

// Copy assignment operator
WrongCat &WrongCat::operator=(const WrongCat &other) {
  if (this != &other)
    WrongAnimal::operator=(other);
  return *this;
}

// Getters
const std::string WrongCat::getType(void) const { return _type; }

// Private functions
void WrongCat::makeSound(void) const { std::cout << "Wrong Meow!" << std::endl; }
