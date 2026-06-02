
#include <string>

#ifndef __CONTACT_HPP__
#define __CONTACT_HPP__

class Contact {

private:
  std::string _first_name;
  std::string _last_name;
  std::string _nickname;
  std::string _phone;
  std::string _secret;

public:
  Contact(std::string first_name, std::string last_name, std::string nickname,
          std::string phone, std::string secret);
  Contact();
  ~Contact();

  Contact &operator=(const Contact &);

  std::string getFirstName();
  std::string getLastName();
  std::string getNickname();
  std::string getPhone();
  std::string getSecret();

  bool isEmpty();
};

#endif // !__CONTACT_HPP__
