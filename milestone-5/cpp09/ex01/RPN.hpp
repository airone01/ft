#ifndef RPN_HPP
#define RPN_HPP

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
  std::list<unsigned int> _nbrs;

public:
  // OCF
  RPN();
  RPN(const RPN &);
  RPN operator=(const RPN &);
  ~RPN();

  void parse(const std::string &);
  int calculate() const;
};

#endif // !RPN_HPP
