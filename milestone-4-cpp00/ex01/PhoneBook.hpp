/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PhoneBook.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 12:58:10 by elagouch          #+#    #+#             */
/*   Updated: 2025/06/22 14:36:19 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Contact.hpp"

#ifndef __PHONEBOOK_HPP__
#define __PHONEBOOK_HPP__

class PhoneBook {

private:
  Contact _contacts[8];
  int _count;
  int _next_index;

public:
  PhoneBook(void);
  ~PhoneBook(void);

  Contact getFirstContact(void);
  Contact getContact(const int &id);
  void addContact(const Contact &contact);
  bool isFull(void);
  int getCount(void);
};

#endif // !__PHONEBOOK_HPP__
