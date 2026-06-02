
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
