#ifndef SPAN_HPP
#define SPAN_HPP

#include <vector>

class Span {
private:
  const unsigned int _max;
  std::vector<int> _elems;

public:
  Span(unsigned int max);
  // Span(const Span &);
  // ~Span();
  // Span &operator=(const Span &);

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
};

#endif // !SPAN_HPP
