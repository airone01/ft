/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cat.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 18:30:00 by elagouch          #+#    #+#             */
/*   Updated: 2026/01/12 17:36:15 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cat.hpp"
#include <iostream>
#include <ostream>

// Default constructor
Cat::Cat(void) : Animal("Cat") {}
// Copy constructor
Cat::Cat(const Cat &other) : Animal(other) {}
// Destructor
Cat::~Cat(void) {}

// Copy assignment operator
Cat &Cat::operator=(const Cat &other) {
  if (this != &other)
    Animal::operator=(other);
  return *this;
}

// Getters
const std::string Cat::getType(void) const { return _type; }

// Private functions
void Cat::makeSound(void) const { std::cout << "Meow!" << std::endl; }
