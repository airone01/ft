#ifndef SPAN_HPP
#define SPAN_HPP

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
   * @brief sets element `i` (0 to `end`) to the result of given function `f`
   */
  void populate(unsigned int end, int (*f)(unsigned int i));
};

#endif // !SPAN_HPP
