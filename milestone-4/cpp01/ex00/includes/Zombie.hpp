/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Zombie.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 12:41:18 by elagouch          #+#    #+#             */
/*   Updated: 2025/08/21 16:23:47 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __ZOMBIE_HPP__
#define __ZOMBIE_HPP__

#include <string>

class Zombie {
public:
  Zombie(const std::string &name);
  ~Zombie();

  void announce(void);

private:
  const std::string _name;
};

// newZombie.cpp
Zombie *newZombie(std::string name);
// randomChump.cpp
void randomChump(std::string name);

#endif // !__ZOMBIE_HPP__
