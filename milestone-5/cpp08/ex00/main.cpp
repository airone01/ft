#include "easyfind.hpp"
#include <deque>
#include <iostream>
#include <list>
#include <vector>

int main(void) {
  // VECTOR
  {
    std::vector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    v.push_back(42);

    std::cout << "found " << easyfind(v, 42) << std::endl;
  }

  // LIST
  {
    std::list<int> l;
    l.push_back(1);
    l.push_back(2);
    l.push_back(3);
    l.push_back(42);

    std::cout << "found " << easyfind(l, 42) << std::endl;
  }

  // DEQUE
  {
    std::deque<int> d;
    d.push_back(1);
    d.push_back(2);
    d.push_back(3);
    d.push_back(42);

    std::cout << "found " << easyfind(d, 42) << std::endl;
  }

  return 0;
}
