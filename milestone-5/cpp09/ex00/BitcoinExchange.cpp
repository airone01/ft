#include "BitcoinExchange.hpp"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <sys/stat.h>
#include <unistd.h>

BitcoinExchange::BitcoinExchange() {}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &other) {
  *this = other;
}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &other) {
  if (this != &other) {
    this->_database = other._database;
  }
  return *this;
}

BitcoinExchange::~BitcoinExchange() {}

/**
 * @brief trims whitespaces from a line
 */
std::string BitcoinExchange::_trim(const std::string &str) {
  size_t first = str.find_first_not_of(" \t");
  if (std::string::npos == first)
    return str;
  size_t last = str.find_last_not_of(" \t");
  return str.substr(first, (last - first + 1));
}

bool is_file(const std::string &filename) {
  struct stat s;
  if (stat(filename.c_str(), &s) == 0) {
    // S_ISDIR checks mode bit
    if (s.st_mode & S_IFREG)
      return true;
    return false;
  }
  return false;
}

void check_file(const std::string &filename) {
  if (access(filename.c_str(), R_OK) != 0)
    throw std::runtime_error("path could not be read");
  if (!is_file(filename))
    throw std::runtime_error("path is not a file");
}

/**
 * @brief reads and load a database file to memory
 */
void BitcoinExchange::loadDatabase(const std::string &filename) {
  check_file(filename);
  std::ifstream file(filename.c_str());
  if (!file.is_open())
    throw std::runtime_error("could not open database file.");

  std::string line;
  // skip header line
  std::getline(file, line);

  while (std::getline(file, line)) {
    if (line.empty())
      continue;

    size_t commaPos = line.find(',');
    if (commaPos == std::string::npos)
      continue;

    std::string date = _trim(line.substr(0, commaPos));
    std::string rateStr = _trim(line.substr(commaPos + 1));

    float rate = static_cast<float>(std::atof(rateStr.c_str()));
    _database[date] = rate;
  }
  file.close();
}

bool BitcoinExchange::_isValidDate(const std::string &s) {
  // length check
  if (s.length() != 10)
    return false;
  // chars checks
  if (s.find_first_not_of("0123456789-") != std::string::npos)
    return false;
  // '-' checks
  if (std::count(s.begin(), s.end(), '-') != 2 || s[4] != '-' || s[7] != '-')
    return false;

  int year = std::atoi(s.substr(0, 4).c_str());
  int month = std::atoi(s.substr(5, 2).c_str());
  int day = std::atoi(s.substr(8, 2).c_str());

  if (year < 0 || month < 1 || month > 12 || day < 1 || day > 31)
    return false;

  // basic validation for days in month could be added here
  // but strictly speaking, checking format YYYY-MM-DD is the priority.
  if (month == 2 && day > 29)
    return false; // simple leap year check omission for brevity unless required
  if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30)
    return false;

  return true;
}

bool BitcoinExchange::_isValidValue(const std::string &s, float &value) {
  // non-num
  if (s.find_first_not_of("0123456789.") != std::string::npos)
    return false;
  // only one dot max
  if (std::count(s.begin(), s.end(), '.') > 1)
    return false;

  char *end;
  value = static_cast<float>(std::strtod(s.c_str(), &end));
  if (*end != '\0')
    return false;

  // check if conversion failed or didn't consume full string
  return !(s.empty() || end == s.c_str());
}

float BitcoinExchange::_getExchangeRate(const std::string &date) {
  if (_database.empty())
    return 0.0f;

  // std::map::lower_bound returns the first element that is NOT considered to
  // go before k. i.e., it returns iterator to >= date
  std::map<std::string, float>::iterator it = _database.lower_bound(date);

  // If exact match found
  if (it != _database.end() && it->first == date) {
    return it->second;
  }

  // If map begins after this date, we have no data
  if (it == _database.begin()) {
    return 0.0f; // Or handle as error
  }

  // Otherwise, go back one step to find the closest lower date
  --it;
  return it->second;
}

void BitcoinExchange::processInput(const std::string &filename) {
  check_file(filename);
  std::ifstream file(filename.c_str());
  if (!file.is_open())
    throw std::runtime_error("could not open query file.");

  std::string line;
  bool first = true;
  while (std::getline(file, line)) {
    if (line.empty() || (first && line == "date | value"))
      continue;
    first = false;

    size_t pipePos = line.find(" | ");
    if (pipePos == std::string::npos) {
      std::cout << "error: invalid input \"" << line << "\"" << std::endl;
      continue;
    }

    std::string date = _trim(line.substr(0, pipePos));
    std::string valueStr = _trim(line.substr(pipePos + 3));
    float value;

    if (!_isValidDate(date) || !_isValidValue(valueStr, value)) {
      std::cout << "error: invalid input \"" << line << "\"" << std::endl;
      continue;
    }

    if (value < 0) {
      std::cout << "error: not a positive number." << std::endl;
      continue;
    }

    // Constraint: value must be between 0 and 1000
    if (value > 1000.0f) {
      std::cout << "error: too large a number." << std::endl;
      continue;
    }

    float rate = _getExchangeRate(date);
    std::cout << date << " => " << value << " = " << (value * rate)
              << std::endl;
  }
  file.close();
}
