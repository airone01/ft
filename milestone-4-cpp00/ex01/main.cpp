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

void main_menu(PhoneBook &pb);
void add_contact(PhoneBook &pb);
void display_contacts(PhoneBook &pb);
std::string truncate_field(const std::string &field);
void display_contact_details(Contact &contact);
void search_contacts(PhoneBook &pb);
void quit_app();

int main() {
  PhoneBook pb;
  main_menu(pb);
  return 0;
}

void main_menu(PhoneBook &pb) {
  std::string inln;
  do {
    std::cout << std::endl << "PhoneBook menu options:" << std::endl;
    std::cout << "ADD    Add a contact" << std::endl;
    std::cout << "SEARCH Search for a contact" << std::endl;
    std::cout << "EXIT   Quit the app" << std::endl;
    std::cout << "> ";

    // eof
    if (!std::getline(std::cin, inln)) {
      quit_app();
    }

    if (inln == "ADD") {
      add_contact(pb);
    } else if (inln == "SEARCH") {
      search_contacts(pb);
    } else if (inln == "EXIT") {
      quit_app();
    } else {
      std::cout << std::endl << inln << ": invalid command." << std::endl;
    }
  } while (true);
}

void quit_app() {
  std::cout << std::endl;
  std::exit(0);
}

std::string ask(std::string prompt) {
  std::string response;
  bool loop = true;
  do {
    std::cout << std::endl << prompt;
    if (!std::getline(std::cin, response)) {
      quit_app();
    }
    if (response.empty()) {
      std::cout << "This cannot be empty. Try again." << std::endl;
    } else
      loop = false;
  } while (loop);
  return response;
}

void add_contact(PhoneBook &pb) {
  std::string inln;

  if (pb.isFull()) {
    std::cout << std::endl
              << "PhoneBook is full, adding a new contact will remove '"
              << pb.getFirstContact().getFirstName() << "', confirm? [y/n] ";

    // eof
    if (!std::getline(std::cin, inln)) {
      quit_app();
    }

    if (inln == "y" || inln == "Y") {
    } else {
      std::cout << "Aborting." << std::endl;
      return;
    }
  }

  std::string first_name = ask("First name: ");
  std::string last_name = ask("Last name: ");
  std::string nickname = ask("Nickname: ");
  std::string phone = ask("Phone number: ");
  std::string secret = ask("Darkest secret: ");
  std::cout << std::endl;

  Contact new_contact(first_name, last_name, nickname, phone, secret);
  pb.addContact(new_contact);
}

void search_contacts(PhoneBook &pb) {
  if (pb.getCount() == 0) {
    std::cout << std::endl << "No contacts in phonebook." << std::endl;
    return;
  }

  std::cout << std::endl
            << "|" << std::setw(10) << "Index" << "|" << std::setw(10)
            << "First Name" << "|" << std::setw(10) << "Last Name" << "|"
            << std::setw(10) << "Nickname" << "|" << std::endl
            << "|----------|----------|----------|----------|" << std::endl;

  for (int i = 0; i < pb.getCount(); i++) {
    Contact contact = pb.getContact(i);
    if (!contact.isEmpty()) {
      std::cout << "|" << std::setw(10) << i << "|" << std::setw(10)
                << truncate_field(contact.getFirstName()) << "|"
                << std::setw(10) << truncate_field(contact.getLastName()) << "|"
                << std::setw(10) << truncate_field(contact.getNickname()) << "|"
                << std::endl;
    }
  }

  int index;
  bool valid_input = false;

  do {
    std::cout << std::endl
              << "Enter contact index to view details (0-"
              << (pb.getCount() - 1) << "): ";
    std::string inln;

    if (!std::getline(std::cin, inln)) {
      quit_app();
    }

    // input is empty
    if (inln.empty()) {
      std::cout << "Please enter a number." << std::endl;
      continue;
    }

    std::istringstream iss(inln);
    iss >> index;

    // parsing failed or there are leftover characters
    if (iss.fail() || !iss.eof()) {
      std::cout << "Invalid input. Please enter a valid number." << std::endl;
      continue;
    }

    // check if index is in valid range
    if (index < 0 || index >= pb.getCount()) {
      std::cout << "Index out of range. Please enter a number between 0 and "
                << (pb.getCount() - 1) << "." << std::endl;
      continue;
    }

    valid_input = true;

  } while (!valid_input);

  Contact selected_contact = pb.getContact(index);
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
  std::cout << "    First Name: " << contact.getFirstName() << std::endl;
  std::cout << "     Last Name: " << contact.getLastName() << std::endl;
  std::cout << "      Nickname: " << contact.getNickname() << std::endl;
  std::cout << "         Phone: " << contact.getPhone() << std::endl;
  std::cout << "Darkest Secret: " << contact.getSecret() << std::endl;
}
