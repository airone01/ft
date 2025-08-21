/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanB.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 17:27:51 by elagouch          #+#    #+#             */
/*   Updated: 2025/08/21 18:02:34 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __HUMAN_B_HPP__
#define __HUMAN_B_HPP__

#include "Weapon.hpp"
#include <string>

class HumanB {

public:
  HumanB();
  HumanB(const HumanB &);
  HumanB(const std::string &name); // No weapon in constructor
  ~HumanB();

  HumanB &operator=(const HumanB &);

  void setWeapon(Weapon);

  void attack();

private:
  std::string _name;
  Weapon *_weapon;
};

#endif // !__HUMAN_B_HPP__
