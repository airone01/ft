
#include "PhoneBook.hpp"

PhoneBook::PhoneBook() : _count(0), _next_index(0) {}

PhoneBook::~PhoneBook() {}

Contact PhoneBook::getFirstContact() { return _contacts[_next_index]; }

Contact PhoneBook::getContact(const int &id) { return _contacts[id]; }

void PhoneBook::addContact(const Contact &contact) {
  _contacts[_next_index] = contact;
  _next_index = (_next_index + 1) % 8;
  if (_count < 8)
    _count++;
}

bool PhoneBook::isFull() { return _count >= 8; }

int PhoneBook::getCount() { return _count; }
