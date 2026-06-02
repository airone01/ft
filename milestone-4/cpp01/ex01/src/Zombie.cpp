
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
