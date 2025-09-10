/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dog.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 18:30:00 by elagouch          #+#    #+#             */
/*   Updated: 2025/09/10 13:00:21 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Dog.hpp"
#include <iostream>
#include <ostream>

// Default constructor
Dog::Dog(void) : Animal("Dog") {};
// Copy constructor
Dog::Dog(const Dog &other) : Animal(other) {};
// Destructor
Dog::~Dog(void) {}

// Getters
const std::string Dog::getType(void) const { return _type; }

// Private functions
void Dog::makeSound(void) const { std::cout << "Woof!" << std::endl; }
