/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScavTrap.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 13:35:49 by elagouch          #+#    #+#             */
/*   Updated: 2025/08/27 15:58:16 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __SCAVTRAP_HPP__
#define __SCAVTRAP_HPP__

#include "ClapTrap.hpp"

class ScavTrap : public ClapTrap {

public:
  ScavTrap();
  ScavTrap(const ScavTrap &);
  ~ScavTrap();

  ScavTrap(const std::string &name);

  ScavTrap &operator=(const ScavTrap &);

  void attack(const std::string &);
  void guardGate(void);
};

#endif // !__SCAVTRAP_HPP__
