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

#ifndef PHONEBOOK_HPP
#define PHONEBOOK_HPP

class PhoneBook {

private:
  Contact _contacts[8];
  int _count;
  int _next_index;

public:
  PhoneBook();
  ~PhoneBook();

  Contact getFirstContact();
  Contact getContact(int id);
  void addContact(Contact contact);
  bool isFull();
  int getCount();

private:
  void _incrAllContacts();
};

#endif // !PHONEBOOK_HPP
