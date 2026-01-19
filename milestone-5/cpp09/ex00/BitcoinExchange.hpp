#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <cstdlib>
#include <map>
#include <string>

class BitcoinExchange {
private:
  std::map<std::string, float> _database;

  std::string _trim(const std::string &str);
  bool _isValidDate(const std::string &date);
  bool _isValidValue(const std::string &valueStr, float &value);
  float _getExchangeRate(const std::string &date);

public:
  BitcoinExchange();
  BitcoinExchange(const BitcoinExchange &other);
  BitcoinExchange &operator=(const BitcoinExchange &other);
  ~BitcoinExchange();

  void loadDatabase(const std::string &filename);
  void processInput(const std::string &filename);
};

#endif
