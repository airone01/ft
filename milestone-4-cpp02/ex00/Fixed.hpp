/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 16:36:26 by elagouch          #+#    #+#             */
/*   Updated: 2025/08/26 17:23:24 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __FIXED_HPP__
#define __FIXED_HPP__

class Fixed {

public:
  Fixed();
  Fixed(const Fixed &);
  Fixed(const int &);
  Fixed(const float &);
  ~Fixed();

  Fixed &operator=(const Fixed &);

  int getRawBits(void) const;

  void setRawBits(int const);

private:
  int _val;
  static const int _bits; // Number of fractional bits.
};

#endif // !__FIXED_HPP__
