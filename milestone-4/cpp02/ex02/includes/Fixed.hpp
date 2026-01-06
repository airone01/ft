/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 16:36:26 by elagouch          #+#    #+#             */
/*   Updated: 2025/08/26 19:00:19 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __FIXED_HPP__
#define __FIXED_HPP__

#include <ostream>
class Fixed {

public:
  Fixed();
  Fixed(const Fixed &);
  Fixed(const int &);
  Fixed(const float &);
  ~Fixed();

  Fixed &operator=(const Fixed &);

  int getRawBits(void) const;
  int toInt(void) const;
  float toFloat(void) const;

  void setRawBits(int const);

  inline bool operator>(const Fixed &) const;
  inline bool operator<(const Fixed &) const;
  inline bool operator==(const Fixed &) const;
  inline bool operator!=(const Fixed &) const;
  inline bool operator<=(const Fixed &) const;
  inline bool operator>=(const Fixed &) const;

  Fixed operator+(const Fixed &) const;
  Fixed operator-(const Fixed &) const;
  Fixed operator*(const Fixed &) const;
  Fixed operator/(const Fixed &) const;

  Fixed &operator++();   // prefix, increment
  Fixed operator++(int); // postfix, increment and return original
  Fixed &operator--();   // prefix
  Fixed operator--(int); // postfix

  static Fixed &min(Fixed &, Fixed &);
  static const Fixed &min(const Fixed &, const Fixed &);
  static Fixed &max(Fixed &, Fixed &);
  static const Fixed &max(const Fixed &, const Fixed &);

private:
  int _val;
  static const int _bits; // Number of fractional bits.
};

std::ostream &operator<<(std::ostream &os, const Fixed &other);

#endif // !__FIXED_HPP__
