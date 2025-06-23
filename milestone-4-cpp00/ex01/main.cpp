/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 12:54:24 by elagouch          #+#    #+#             */
/*   Updated: 2025/06/22 14:41:06 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PhoneBook.hpp"
#include <cstdio>
#include <iostream>
#include <ostream>
#include <string>

void main_menu(PhoneBook *pb);
void add_contact(PhoneBook *pb);
void display_contacts(PhoneBook *pb);

int main() {
  PhoneBook *pb = new PhoneBook();
  main_menu(pb);
  return 0;
}

void main_menu(PhoneBook *pb) {
  std::string inln;
  do {
    std::cout << std::endl << "PhoneBook menu options:" << std::endl;
    std::cout << "ADD    Add a contact" << std::endl;
    std::cout << "SEARCH Search for a contact" << std::endl;
    std::cout << "EXIT   Quit the app" << std::endl;
    std::cout << "> ";
    std::cin >> inln;

    if (inln == "ADD") {
      add_contact(pb);
    } else if (inln == "EXIT") {
      break;
    } else {
      std::cout << std::endl << inln << ": invalid command." << std::endl;
    }
  } while (true);
}

void add_contact(PhoneBook *pb) {
  std::string inln;

  if (pb->isFull()) {
    std::cout << std::endl
              << "PhoneBook is full, adding a new contact will remove '"
              << pb->getFirstContact().getFirstName() << "', confirm? [y/n] ";
    std::cin >> inln;

    if (inln == "y" || inln == "Y") {
    } else {
      std::cout << "Aborting." << std::endl;
    }
  }

  std::string first_name;
  std::string last_name;
  std::string nickname;
  std::string phone;
  std::string secret;
  std::cout << std::endl << "First name: ";
  std::cin >> first_name;
  std::cout << "Last name: ";
  std::cin >> last_name;
  std::cout << "Nickname: ";
  std::cin >> nickname;
  std::cout << "Phone number: ";
  std::cin >> phone;
  std::cout << "Darkest secret: ";
  std::getline(std::cin, secret);

  pb->addContact(*new Contact(first_name, last_name, nickname, phone, secret));
}
