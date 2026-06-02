
#ifndef __FRAGTRAP_HPP__
#define __FRAGTRAP_HPP__

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

#endif // !__FRAGTRAP_HPP__
