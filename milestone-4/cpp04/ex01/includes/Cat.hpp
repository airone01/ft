
#ifndef __CAT_HPP__
#define __CAT_HPP__

#include "Animal.hpp"
#include "Brain.hpp"

class Cat : public Animal {

public:
  Cat(void);
  Cat(const Cat &);
  virtual ~Cat(void);
  // vitual forces to run the destructor of the base class Animal.
  // this avoids leaks.

  Cat &operator=(const Cat &);

  const std::string getType(void) const;

  void makeSound(void) const;

  Brain *getBrain(void) const;

private:
  Brain *_brain;
};

#endif // !__CAT_HPP__
