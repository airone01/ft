/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Zombie.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 12:38:11 by elagouch          #+#    #+#             */
/*   Updated: 2025/08/21 16:55:40 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"
#include <iostream>
#include <ostream>

Zombie::Zombie(const std::string &name) : _name(name) {}
Zombie::Zombie() {}

Zombie::~Zombie() {}

void Zombie::setName(const std::string &name) { _name = name; }

void Zombie::announce() {
  std::cout << _name << ": BraiiiiiiinnnzzzZ..." << std::endl;
}
