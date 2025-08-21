/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Zombie.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 12:38:11 by elagouch          #+#    #+#             */
/*   Updated: 2025/08/20 12:58:31 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"
#include <iostream>
#include <ostream>

Zombie::Zombie(const std::string &name) : _name(name) {}

Zombie::~Zombie() {}

void Zombie::announce() {
  std::cout << _name << ": BraiiiiiiinnnzzzZ..." << std::endl;
}
