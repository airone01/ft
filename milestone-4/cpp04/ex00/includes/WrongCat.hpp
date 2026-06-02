
#ifndef __WRONGCAT_HPP__
#define __WRONGCAT_HPP__

#include "WrongAnimal.hpp"

class WrongCat : public WrongAnimal {

public:
  WrongCat(void);
  WrongCat(const WrongCat &);
  ~WrongCat(void); // not virtual

  WrongCat &operator=(const WrongCat &);

  const std::string getType(void) const;

  void makeSound(void) const; // not virtual
};

#endif // !__WRONGCAT_HPP__
