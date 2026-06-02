
#include "Weapon.hpp"

// Default constructor
Weapon::Weapon() : _type("lightsaber") {}
// Copy constructor
Weapon::Weapon(const Weapon &other) : _type(other._type) {}
// Parameterized import
Weapon::Weapon(const std::string &type) : _type(type) {}

// Destructor
Weapon::~Weapon() {}

// Getters
std::string &Weapon::getType(void) { return _type; }

// Setters
void Weapon::setType(const std::string &newType) { _type = newType; }
