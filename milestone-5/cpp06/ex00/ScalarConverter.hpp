#ifndef SCALARCONVERTER_HPP
#define SCALARCONVERTER_HPP

#include <string>

class ScalarConverter {
public:
  static void convert(const std::string &);

private:
  // 98 doesn't have `= delete` so this will do
  ScalarConverter();
  ScalarConverter(const ScalarConverter &);
  ~ScalarConverter();
  ScalarConverter &operator=(const ScalarConverter &);
};

#endif // !SCALARCONVERTER_HPP
