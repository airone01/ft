
#include <iomanip>
#include <iostream>
#include <string>

int main(void) {
  std::string str = "HI THIS IS BRAINZ";
  std::string *stringPTR = &str;
  std::string &stringREF = str;

  std::cout << "Memory address of the string variable: " << &str << std::endl
            << std::setw(39)
            << "Memory address held by stringPTR: " << stringPTR << std::endl
            << std::setw(39)
            << "Memory address held by stringREF: " << &stringREF << std::endl
            << std::endl;
  std::cout << std::setw(31) << "Value of the string variable: " << str
            << std::endl
            << std::setw(31) << "Value pointed to by stringPTR: " << *stringPTR
            << std::endl
            << std::setw(31) << "Value pointed to by stringREF: " << stringREF
            << std::endl;
}
