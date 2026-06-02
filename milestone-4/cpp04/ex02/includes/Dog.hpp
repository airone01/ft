
#ifndef __DOG_HPP__
#define __DOG_HPP__

#include "AAnimal.hpp"
#include "Brain.hpp"

class Dog : public AAnimal {

public:
  Dog(void);
  Dog(const Dog &);
  ~Dog(void);
  // vitual forces to run the destructor of the base class Animal.
  // this avoids leaks.

  Dog &operator=(const Dog &);

  const std::string getType(void) const;

  void makeSound(void) const;

  Brain *getBrain(void) const;

private:
  Brain *_brain;
};

#endif // !__DOG_HPP__
