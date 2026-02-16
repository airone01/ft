#include "BitcoinExchange.hpp"
#include <algorithm>
#include <ctime>
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
  // dates before 70 are cringe :-O
  if (year < 1970)
    throw std::runtime_error("invalid date");
  int month = std::atoi(s.substr(5, 2).c_str());
  int day = std::atoi(s.substr(8, 2).c_str());

  struct tm tm = {};
  tm.tm_year = year - 1900;
  tm.tm_mon = month - 1;
  tm.tm_mday = day;
  tm.tm_isdst = -1; // let mktime determine if we use daylight saving by itself

  time_t result = std::mktime(&tm);
  if (result == -1)
    throw std::runtime_error("invalid date");

  // if result was changed (normalized), then that means that the original was
  // invalid, hence we crash
  if (tm.tm_year != (year - 1900) || tm.tm_mon != (month - 1) ||
      tm.tm_mday != day)
    throw std::runtime_error("invalid date");
  return true;
}

bool BitcoinExchange::_isValidValue(const std::string &s, float &value) {
  // non-num
  if (s.find_first_not_of("0123456789.-") != std::string::npos)
    return false;
  // make sure '-' is at index 0
  if (s.find('-') != std::string::npos && s[0] != '-')
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

  // std::map::lower_bound returns the first element that is NOT considered
  // to go before k. i.e., it returns iterator to >= date
  std::map<std::string, float>::iterator it = _database.lower_bound(date);

  // if exact match found
  if (it != _database.end() && it->first == date)
    return it->second;

  // if map begins after this date, we have no data
  if (it == _database.begin())
    throw std::runtime_error("date predates database");

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
    try {
      if ((first && line == "date | value"))
        continue;
      if (line.empty()) {
        std::cout << std::endl;
        continue;
      }
      first = false;

      size_t pipePos = line.find(" | ");
      if (pipePos == std::string::npos)
        throw std::runtime_error("unrecognized input");

      std::string date = _trim(line.substr(0, pipePos));
      std::string valueStr = _trim(line.substr(pipePos + 3));
      float value;

      if (!_isValidDate(date))
        throw std::runtime_error("invalid date format");
      if (!_isValidValue(valueStr, value))
        throw std::runtime_error("invalid value format");
      if (value < 0) // in thory should never happen
        throw std::runtime_error("value is not a positive number");
      if (value > 1e3f)
        throw std::runtime_error("value is too large a number");

      float rate = _getExchangeRate(date); // can thow
      std::cout << date << " => " << value << " = " << (value * rate)
                << std::endl;
    } catch (const std::exception &e) {
      std::cout << "error: " << e.what() << " in \"" << line << "\""
                << std::endl;
      continue;
    }
  }
  file.close();
}
