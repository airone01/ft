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
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <ostream>
#include <sstream>
#include <string>

void main_menu(PhoneBook *pb);
void add_contact(PhoneBook *pb);
void display_contacts(PhoneBook *pb);
std::string truncate_field(const std::string &field);
void display_contact_details(Contact &contact);
void search_contacts(PhoneBook *pb);
void quit_app(PhoneBook *pb);

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

    if (!std::getline(std::cin, inln)) {
      // EOF detected (Ctrl+D)
      quit_app(pb);
    }

    if (inln == "ADD") {
      add_contact(pb);
    } else if (inln == "SEARCH") {
      search_contacts(pb);
    } else if (inln == "EXIT") {
      quit_app(pb);
    } else {
      std::cout << std::endl << inln << ": invalid command." << std::endl;
    }
  } while (true);
}

void quit_app(PhoneBook *pb) {
  std::cout << std::endl;
  delete pb;
  std::exit(0);
}

void add_contact(PhoneBook *pb) {
  std::string inln;

  if (pb->isFull()) {
    std::cout << std::endl
              << "PhoneBook is full, adding a new contact will remove '"
              << pb->getFirstContact().getFirstName() << "', confirm? [y/n] ";

    if (!std::getline(std::cin, inln)) {
      std::cout << std::endl;
      return;
    }

    if (inln == "y" || inln == "Y") {
    } else {
      std::cout << "Aborting." << std::endl;
      return;
    }
  }

  std::string first_name;
  std::string last_name;
  std::string nickname;
  std::string phone;
  std::string secret;

  std::cout << std::endl << "First name: ";
  if (!std::getline(std::cin, first_name)) {
    quit_app(pb);
  }

  std::cout << "Last name: ";
  if (!std::getline(std::cin, last_name)) {
    quit_app(pb);
  }

  std::cout << "Nickname: ";
  if (!std::getline(std::cin, nickname)) {
    quit_app(pb);
  }

  std::cout << "Phone number: ";
  if (!std::getline(std::cin, phone)) {
    quit_app(pb);
  }

  std::cout << "Darkest secret: ";
  if (!std::getline(std::cin, secret)) {
    quit_app(pb);
  }
  std::cout << std::endl;

  Contact new_contact(first_name, last_name, nickname, phone, secret);
  pb->addContact(new_contact);
}

void search_contacts(PhoneBook *pb) {
  if (pb->getCount() == 0) {
    std::cout << std::endl << "No contacts in phonebook." << std::endl;
    return;
  }

  std::cout << std::endl;
  std::cout << "|" << std::setw(10) << "Index" << "|" << std::setw(10)
            << "First Name" << "|" << std::setw(10) << "Last Name" << "|"
            << std::setw(10) << "Nickname" << "|" << std::endl;
  std::cout << "|----------|----------|----------|----------|" << std::endl;

  for (int i = 0; i < pb->getCount(); i++) {
    Contact contact = pb->getContact(i);
    if (!contact.isEmpty()) {
      std::cout << "|" << std::setw(10) << i << "|" << std::setw(10)
                << truncate_field(contact.getFirstName()) << "|"
                << std::setw(10) << truncate_field(contact.getLastName()) << "|"
                << std::setw(10) << truncate_field(contact.getNickname()) << "|"
                << std::endl;
    }
  }

  bool fail = true;
  int index;
  do {
    std::cout << std::endl
              << "Enter contact index to view details (" << pb->getCount()
              << " contacts): ";
    std::string inln;
    if (!std::getline(std::cin, inln))
		quit_app(pb);
    std::istringstream iss(inln);
    iss >> index;
    if (iss.fail()) {
      std::cout << "Bad number." << std::endl;
    } else {
      fail = false;
    }
  } while (fail);

  if (std::cin.fail() || index < 0 || index >= pb->getCount()) {
    std::cin.clear();
    std::cin.ignore(1000, '\n');
    std::cout << "Invalid index." << std::endl;
    return;
  }

  Contact selected_contact = pb->getContact(index);
  if (selected_contact.isEmpty()) {
    std::cout << "No contact at this index." << std::endl;
    return;
  }

  display_contact_details(selected_contact);
}

std::string truncate_field(const std::string &field) {
  if (field.length() > 10) {
    return field.substr(0, 9) + ".";
  }
  return field;
}

void display_contact_details(Contact &contact) {
  std::cout << std::endl << "Contact Details:" << std::endl;
  std::cout << "First Name: " << contact.getFirstName() << std::endl;
  std::cout << "Last Name: " << contact.getLastName() << std::endl;
  std::cout << "Nickname: " << contact.getNickname() << std::endl;
  std::cout << "Phone: " << contact.getPhone() << std::endl;
  std::cout << "Darkest Secret: " << contact.getSecret() << std::endl;
}
