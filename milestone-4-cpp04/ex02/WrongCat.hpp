/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WrongCat.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 15:42:20 by elagouch          #+#    #+#             */
/*   Updated: 2025/09/10 14:58:02 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
