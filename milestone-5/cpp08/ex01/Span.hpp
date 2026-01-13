#ifndef SPAN_HPP
#define SPAN_HPP

#include <iterator>
#include <stdexcept>
#include <vector>

class Span {
private:
  const unsigned int _max;
  std::vector<int> _elems;

public:
  Span(unsigned int max);
  Span(const Span &);
  ~Span();
  Span &operator=(const Span &);

  /**
   * @throws exception
   */
  void addNumber(int n);

  /**
   * @throws exception
   */
  int shortestSpan() const;
  /**
   * @throws exception
   */
  int longestSpan() const;

  /**
   * @brief reproduces the behavior of `::insert` but safe
   */
  template <typename InputIt> void insert(InputIt begin, InputIt end) {
    unsigned long dist = static_cast<unsigned long>(std::distance(begin, end));
    if (_elems.size() + dist > _max)
      throw std::out_of_range("not enough space in Span to add this range");
    _elems.insert(_elems.end(), begin, end);
  }
};

#endif // !SPAN_HPP
