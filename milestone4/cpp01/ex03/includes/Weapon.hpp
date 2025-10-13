/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Weapon.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 17:20:42 by elagouch          #+#    #+#             */
/*   Updated: 2025/08/21 17:44:54 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __WEAPON_HPP__
#define __WEAPON_HPP__

#include <string>

class Weapon {
public:
  Weapon();
  Weapon(const Weapon &);
  Weapon(const std::string &nType);
  ~Weapon();

  std::string &getType();
  void setType(const std::string &newType);

private:
  std::string _type;
};

#endif // !__WEAPON_HPP__
