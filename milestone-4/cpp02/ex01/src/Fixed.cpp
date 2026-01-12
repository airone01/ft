/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 16:40:04 by elagouch          #+#    #+#             */
/*   Updated: 2026/01/12 17:35:41 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"
#include <iostream>
#include <math.h>

const int Fixed::_bits = 8;

// Default constructor
Fixed::Fixed() : _val(0) {
  std::cout << "Default constructor called" << std::endl;
}
// Parameterized constructors
Fixed::Fixed(const int &otherVal) : _val(otherVal << _bits) {
  std::cout << "Int constructor called" << std::endl;
}
Fixed::Fixed(const float &otherVal) : _val(roundf(otherVal * (1 << _bits))) {
  std::cout << "Float constructor called" << std::endl;
}
// Copy constructor
Fixed::Fixed(const Fixed &other) : _val(other._val) {
  std::cout << "Copy constructor called" << std::endl;
}
// Destructor
Fixed::~Fixed() { std::cout << "Destructor called" << std::endl; }

// Copy asignment operator
Fixed &Fixed::operator=(const Fixed &other) {
  std::cout << "Copy assignment operator called" << std::endl;
  if (this != &other) {
    this->setRawBits(other.getRawBits());
  }
  return *this;
}

// Getters
int Fixed::getRawBits(void) const { return _val; }
int Fixed::toInt(void) const { return getRawBits() >> _bits; }
float Fixed::toFloat(void) const {
  return ((float)getRawBits() / (1 << _bits));
}

// Setters
void Fixed::setRawBits(const int newVal) { _val = newVal; }

// `<<` operator
std::ostream &operator<<(std::ostream &os, const Fixed &other) {
  os << other.toFloat();
  return os;
}
