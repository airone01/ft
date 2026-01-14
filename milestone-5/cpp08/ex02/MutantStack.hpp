#ifndef MUTANTSTACK_HPP
#define MUTANTSTACK_HPP

#include <stack>

template <class T> class MutantStack : public std::stack<T> {
public:
  // OCF
  MutantStack() {}
  MutantStack(const MutantStack &other) : std::stack<T>(other) {}
  MutantStack &operator=(const MutantStack &other) {
    std::stack<T>::operator=(other);
    return *this;
  }
  ~MutantStack() {}

  typedef typename std::stack<T>::container_type::iterator iterator;
  typedef typename std::stack<T>::container_type::const_iterator const_iterator;
  typedef
      typename std::stack<T>::container_type::reverse_iterator reverse_iterator;
  typedef typename std::stack<T>::container_type::const_reverse_iterator
      const_reverse_iterator;

  iterator begin() { return this->c.begin(); };
  const_iterator begin() const { return this->c.begin(); };

  iterator end() { return this->c.end(); };
  const_iterator end() const { return this->c.end(); };

  const_iterator cbegin() { return this->c.cbegin(); };
  const_iterator cbegin() const { return this->c.cbegin(); };

  const_iterator cend() { return this->c.cend(); };
  const_iterator cend() const { return this->c.cend(); };

  reverse_iterator rbegin() { return this->c.rbegin(); };
  const_reverse_iterator rbegin() const { return this->c.rbegin(); };

  reverse_iterator rend() { return this->c.rend(); };
  const_reverse_iterator rend() const { return this->c.rend(); };

  const_reverse_iterator crbegin() { return this->c.crbegin(); };
  const_reverse_iterator crbegin() const { return this->c.crbegin(); };

  const_reverse_iterator crend() { return this->c.crend(); };
  const_reverse_iterator crend() const { return this->c.crend(); };
};

#endif // !MUTANTSTACK_HPP
