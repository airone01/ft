/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PhoneBook.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 12:57:23 by elagouch          #+#    #+#             */
/*   Updated: 2025/06/22 14:36:37 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PhoneBook.hpp"

PhoneBook::PhoneBook(): _count(0), _next_index(0) {}

Contact PhoneBook::getFirstContact() {
	return _contacts[_next_index];
}

Contact PhoneBook::getContact(int id) { return _contacts[id]; }

void PhoneBook::addContact(Contact contact) {
  _contacts[_next_index] = contact;
  _next_index = (_next_index + 1) % 8;
  if (_count < 8)
    _count++;
}

bool PhoneBook::isFull() { return _count >= 8; }
