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
#include <string>

Contact::Contact(std::string f, std::string l, std::string n, std::string p,
                 std::string s)
    : _first_name(f), _last_name(l), _nickname(n), _phone(p), _secret(s) {}
Contact::Contact()
    : _first_name(""), _last_name(""), _nickname(""), _phone(""), _secret("") {}
Contact::~Contact() {}

std::string Contact::getFirstName() { return _first_name; }
