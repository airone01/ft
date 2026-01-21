#ifndef RPN_HPP
#define RPN_HPP

#include <exception>
#include <list>
#include <string>

typedef enum e_ops {
  ADD,
  SUB,
  MULT,
  DIV
} t_ops;

class RPN {
private:
  std::list<t_ops> _ops;
  std::list<unsigned int> _digs;

public:
  // OCF
  RPN();
  RPN(const RPN &);
  RPN operator=(const RPN &);
  ~RPN();

  void parse(const std::string &);
  int calculate() const;

  class IllegalCharacterException: public std::exception {
  public:
    virtual const char* what() const throw();
  };

  class InvalidRpnException: public std::exception {
  public:
    virtual const char* what() const throw();
  };
};

#endif // !RPN_HPP
