/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WrongAnimal.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 14:28:14 by elagouch          #+#    #+#             */
/*   Updated: 2025/09/10 15:04:00 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __WRONGANIMAL_HPP__
#define __WRONGANIMAL_HPP__

#include <string>

class WrongAnimal {
public:
  WrongAnimal();
  WrongAnimal(const std::string &);
  WrongAnimal(const WrongAnimal &);
  ~WrongAnimal(); // not virtual

  WrongAnimal &operator=(const WrongAnimal &obj);

  const std::string getType(void) const;

  void makeSound(void) const; // not virtual

protected:
  std::string _type;
};

#endif // !__WRONGANIMAL_HPP__
