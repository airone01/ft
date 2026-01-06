/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanA.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 17:27:51 by elagouch          #+#    #+#             */
/*   Updated: 2025/08/21 17:50:05 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __HUMAN_A_HPP__
#define __HUMAN_A_HPP__

#include "Weapon.hpp"
#include <string>

class HumanA {

public:
  HumanA();
  HumanA(const HumanA &);
  HumanA(const std::string &name, const Weapon &);
  ~HumanA();

  HumanA &operator=(const HumanA &);

  void attack();

private:
  std::string _name;
  Weapon _weapon;
};

#endif // !__HUMAN_A_HPP__
