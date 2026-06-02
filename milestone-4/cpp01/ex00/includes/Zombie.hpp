
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
