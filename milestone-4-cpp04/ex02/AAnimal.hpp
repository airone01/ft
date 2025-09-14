/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AAnimal.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 15:42:20 by elagouch          #+#    #+#             */
/*   Updated: 2025/09/14 12:33:21 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __AANIMAL_HPP__
#define __AANIMAL_HPP__

#include <string>

class AAnimal {

public:
  AAnimal(void);
  AAnimal(const std::string &);
  AAnimal(const AAnimal &);
  virtual ~AAnimal(void);

  AAnimal &operator=(const AAnimal &);

  const std::string getType(void) const;

  // This is a pure-virtual method, making the class abstract
  // So now, we can't instanciate it :-)
  virtual void makeSound(void) const = 0;

protected:
  std::string _type;
};

#endif // !__AANIMAL_HPP__
