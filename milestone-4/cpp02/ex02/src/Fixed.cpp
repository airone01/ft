/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 16:40:04 by elagouch          #+#    #+#             */
/*   Updated: 2025/08/27 12:36:31 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"
#include <iostream>
#include <math.h>

const int Fixed::_bits = 8;

// Default constructor
Fixed::Fixed() : _val(0) {};
// Parameterized constructors
Fixed::Fixed(const int &otherVal) : _val(otherVal << _bits) {};
Fixed::Fixed(const float &otherVal) : _val(roundf(otherVal * (1 << _bits))) {};
// Copy constructor
Fixed::Fixed(const Fixed &other) : _val(other._val) {}
// Destructor
Fixed::~Fixed() {};

// Copy asignment operator
Fixed &Fixed::operator=(const Fixed &other) {
  if (this != &other) {
    this->setRawBits(other.getRawBits());
  }
  return *this;
};

// Getters
int Fixed::getRawBits(void) const { return _val; }
int Fixed::toInt(void) const { return getRawBits() >> _bits; }
float Fixed::toFloat(void) const {
  return ((float)getRawBits() / (1 << _bits));
}

// Setters
void Fixed::setRawBits(const int newVal) { _val = newVal; }

// Operator overloads: comparison
inline bool Fixed::operator>(const Fixed &other) const {
  return (this->toFloat() > other.toFloat());
}
inline bool Fixed::operator<(const Fixed &other) const {
  return (this->toFloat() < other.toFloat());
}
inline bool Fixed::operator==(const Fixed &other) const {
  return (this->toFloat() == other.toFloat());
}
inline bool Fixed::operator!=(const Fixed &other) const {
  return (!(this == &other));
}
inline bool Fixed::operator<=(const Fixed &other) const {
  return ((this == &other) || (this < &other));
}
inline bool Fixed::operator>=(const Fixed &other) const {
  return ((this == &other) || (this > &other));
}
// Operator overloads: arithmetics
Fixed Fixed::operator+(const Fixed &other) const {
  const Fixed res(this->toFloat() + other.toFloat());
  return res;
}
Fixed Fixed::operator-(const Fixed &other) const {
  const Fixed res(this->toFloat() - other.toFloat());
  return res;
}
Fixed Fixed::operator*(const Fixed &other) const {
  const Fixed res(this->toFloat() * other.toFloat());
  return res;
}
Fixed Fixed::operator/(const Fixed &other) const {
  const Fixed res(this->toFloat() / other.toFloat());
  return res;
}
// Operator overloads: unary
Fixed &Fixed::operator++() {
  _val++;
  return (*this);
}
Fixed Fixed::operator++(int) {
  Fixed old = *this;
  _val++;
  return (old);
}
Fixed &Fixed::operator--() {
  _val--;
  return (*this);
}
Fixed Fixed::operator--(int) {
  Fixed old = *this;
  _val--;
  return (old);
}
// Operator overloads: ostream
std::ostream &operator<<(std::ostream &os, const Fixed &other) {
  os << other.toFloat();
  return os;
}

// Public methods
Fixed &Fixed::min(Fixed &a, Fixed &b) {
  if (a < b)
    return (a);
  return (b);
}
const Fixed &Fixed::min(const Fixed &a, const Fixed &b) {
  if (a < b)
    return (a);
  return (b);
}
Fixed &Fixed::max(Fixed &a, Fixed &b) {
  if (a > b)
    return (a);
  return (b);
}
const Fixed &Fixed::max(const Fixed &a, const Fixed &b) {
  if (a > b)
    return (a);
  return (b);
}
