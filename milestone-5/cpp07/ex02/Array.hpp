#ifndef ARRAY_HPP
#define ARRAY_HPP

#include <stdexcept>

template <class T> class Array {
private:
  T *_elems;
  unsigned int _size;

public:
  ~Array() { delete[] _elems; }

  Array &operator=(const Array<T> &other) {
    if (this == &other)
      return *this;
    delete[] _elems;
    _size = other._size;
    _elems = new T[_size];
    for (unsigned int i = 0; i < _size; i++)
      _elems[i] = other._elems[i];
    return *this;
  }

  Array(const Array<T> &other) : _size(other._size) {
    _elems = new T[_size];
    for (unsigned int i = 0; i < _size; i++)
      _elems[i] = other._elems[i];
  }

  // hmm O_O
  Array() : _elems(new T[0]), _size(0) {}
  Array(unsigned int n) : _size(n) {
    _elems = new T[n];
    for (unsigned int i = 0; i < n; i++) {
      _elems[i] = T();
    }
  }

  T &operator[](unsigned int index) {
    if (index >= _size) {
      throw std::out_of_range("Array index out of bound, exiting");
    }
    return _elems[index];
  }
  const T &operator[](unsigned int index) const {
    if (index >= _size) {
      throw std::out_of_range("Array index out of bound, exiting");
    }
    return _elems[index];
  }

  unsigned int size() const { return _size; }
};

#endif // !ARRAY_HPP
