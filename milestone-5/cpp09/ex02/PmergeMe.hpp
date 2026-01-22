#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <deque>
#include <exception>
#include <iostream>
#include <string>
#include <vector>

class PmergeMe {
private:
  std::vector<unsigned long> _vec;
  std::deque<unsigned long> _deq;

public:
  // OCF
  PmergeMe();
  PmergeMe(const PmergeMe &);
  PmergeMe operator=(const PmergeMe &);
  ~PmergeMe();

  PmergeMe(const std::string &s);

  void sortVector();
  void sortDeque();

  const std::vector<unsigned long> &getVector() const;
  const std::deque<unsigned long> &getDeque() const;

  class InvalidInputException : public std::exception {
    virtual const char *what() const throw();
  };
};

/**
 * @brief formats a container for an ostream
 * @note this exists because `fmt` and other solutions don't exist in 98
 * @note the template shenanigans are to indicate to the compiler to accept only
 * containers for arg `c`
 * @note tested with `std::vector` and `std::deque`
 */
template <template <typename, typename> class Container, typename Alloc>
std::ostream &operator<<(std::ostream &os,
                         const Container<unsigned long, Alloc> &c) {
  typename Container<unsigned long, Alloc>::const_iterator it = c.begin();
  os << "[";
  while (it != c.end()) {
    os << *it;
    if (++it != c.end()) {
      os << ",";
    }
  }
  os << "]";
  return os;
}

std::vector<unsigned long> genJacobsthal(unsigned long len);

#endif // !PMERGEME_HPP
