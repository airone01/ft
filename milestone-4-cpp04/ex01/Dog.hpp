/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dog.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 15:42:20 by elagouch          #+#    #+#             */
/*   Updated: 2025/09/10 12:59:21 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __DOG_HPP__
#define __DOG_HPP__

#include "Animal.hpp"

class Dog : public Animal {

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
