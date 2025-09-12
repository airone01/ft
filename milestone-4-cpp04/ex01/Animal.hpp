/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Animal.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 15:42:20 by elagouch          #+#    #+#             */
/*   Updated: 2025/09/12 16:37:28 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __ANIMAL_HPP__
#define __ANIMAL_HPP__

#include <string>

class Animal {

public:
  Animal(void);
  Animal(const std::string &);
  Animal(const Animal &);
  virtual ~Animal(void);

  Animal &operator=(const Animal &);

  const std::string getType(void) const;

  virtual void makeSound(void) const;

protected:
  std::string _type;
};

#endif // !__ANIMAL_HPP__
