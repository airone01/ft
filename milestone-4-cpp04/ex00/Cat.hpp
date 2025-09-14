/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cat.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 15:42:20 by elagouch          #+#    #+#             */
/*   Updated: 2025/09/10 12:58:50 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __CAT_HPP__
#define __CAT_HPP__

#include "Animal.hpp"

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
};

#endif // !__CAT_HPP__
