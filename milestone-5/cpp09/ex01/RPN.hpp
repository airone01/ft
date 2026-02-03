#ifndef RPN_HPP
#define RPN_HPP

#include <exception>
#include <string>

typedef enum e_ops { ADD = '+', SUB = '-', MULT = '*', DIV = '/' } t_ops;

class RPN {
private:
  // OCF
  RPN();
  RPN(const RPN &);
  RPN operator=(const RPN &);
  ~RPN();

public:
  static void parse(const std::string &);

  class IllegalCharacterException : public std::exception {
  public:
    virtual const char *what() const throw();
  };

  class InvalidRpnException : public std::exception {
  public:
    virtual const char *what() const throw();
  };

  class DivByZeroException : public std::exception {
  public:
    virtual const char *what() const throw();
  };

  class OverflowException : public std::exception {
  public:
    virtual const char *what() const throw();
  };
};

#endif // !RPN_HPP
