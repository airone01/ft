#ifndef ITER_HPP
#define ITER_HPP

// template <typename T> void iter(T *a, const int l, std::function<void(T)>); # C++ 11

template <typename T> void iter(T *v, const int l, void (*f)(T)) {
  for (int i = 0; i < l; i++) {
    f(v[i]);
  }
}

#endif // !ITER_HPP
