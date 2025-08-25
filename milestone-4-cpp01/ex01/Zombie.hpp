/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Zombie.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 12:41:18 by elagouch          #+#    #+#             */
/*   Updated: 2025/08/21 16:55:53 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __ZOMBIE_HPP__
#define __ZOMBIE_HPP__

#include <string>

class Zombie {
public:
  Zombie();
  Zombie(const std::string &name);
  ~Zombie();

  void announce();

  void setName(const std::string &name);

private:
  std::string _name;
};

// zombieHorde.cpp
Zombie *zombieHorde(int N, std::string name);

#endif // !__ZOMBIE_HPP__
