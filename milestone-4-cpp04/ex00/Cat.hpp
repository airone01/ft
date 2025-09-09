/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cat.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 15:42:20 by elagouch          #+#    #+#             */
/*   Updated: 2025/09/08 18:39:51 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __CAT_HPP__
#define __CAT_HPP__

#include "Animal.hpp"

class Cat: public Animal {

public:
  Cat(void);
  Cat(const Animal &);
  virtual ~Cat(void);

  Cat &operator=(const Animal &);

  virtual void makeSound(void);
  // vitual forces to run the destructor of the base class Animal.
  // this avoids leaks.
};

#endif // !__CAT_HPP__
