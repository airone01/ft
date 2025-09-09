/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Animal.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 15:42:20 by elagouch          #+#    #+#             */
/*   Updated: 2025/09/08 18:41:51 by elagouch         ###   ########.fr       */
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
  ~Animal(void);

  Animal &operator=(const Animal &);

  void makeSound(void);

protected:
  std::string _type;
};

#endif // !__ANIMAL_HPP__
