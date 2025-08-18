/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Contact.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 13:33:20 by elagouch          #+#    #+#             */
/*   Updated: 2025/06/22 14:37:41 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Contact.hpp"
#include <cstring>
#include <string>

// Constructors & destructor
Contact::Contact(std::string f, std::string l, std::string n, std::string p,
                 std::string s)
    : _first_name(f), _last_name(l), _nickname(n), _phone(p), _secret(s) {}
Contact::Contact()
    : _first_name(""), _last_name(""), _nickname(""), _phone(""), _secret("") {}
Contact::~Contact() {}

// Getters
std::string Contact::getFirstName() { return _first_name; }
std::string Contact::getLastName() { return _last_name; }
std::string Contact::getNickname() { return _nickname; }
std::string Contact::getPhone() { return _phone; }
std::string Contact::getSecret() { return _secret; }

bool Contact::isEmpty() {
  return (_first_name.size() + _last_name.size() + _nickname.size() +
              _phone.size() + _secret.size() <=
          0);
}
