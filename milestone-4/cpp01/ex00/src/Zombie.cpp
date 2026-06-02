
#include "Zombie.hpp"
#include <iostream>
#include <ostream>

Zombie::Zombie(const std::string &name) : _name(name) {}

Zombie::~Zombie() { std::cout << _name << " is destroyed." << std::endl; }

void Zombie::announce() {
  std::cout << _name << ": BraiiiiiiinnnzzzZ..." << std::endl;
}
