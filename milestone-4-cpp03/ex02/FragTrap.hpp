/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FragTrap.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 13:35:49 by elagouch          #+#    #+#             */
/*   Updated: 2025/08/27 16:11:15 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __SCAVTRAP_HPP__
#define __SCAVTRAP_HPP__

#include "ClapTrap.hpp"

class FragTrap : public ClapTrap {

public:
  FragTrap();
  FragTrap(const FragTrap &);
  ~FragTrap();

  FragTrap(const std::string &name);

  FragTrap &operator=(const FragTrap &);

  void attack(const std::string &);
  void highFivesGuys(void);
};

#endif // !__SCAVTRAP_HPP__
