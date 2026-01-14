#include "MutantStack.hpp"
#include <iostream>
#include <string>
#include <list>

bool assert_test(bool condition, const std::string &name) {
  if (condition)
    std::cout << "[\x1B[32mOK\033[0m] " << name << std::endl;
  else
    std::cout << "[\x1B[31mKO\033[0m] " << name << std::endl;
  return condition;
}

int main(void) {
  {
    MutantStack<int> mstack;
    mstack.push(5);
    mstack.push(17);

    std::list<int> lstack;
    lstack.push_back(5);
    lstack.push_back(17);

    // check top stack
    assert_test(mstack.top() == lstack.back(), "top element matches std::list");

    mstack.pop();
    lstack.pop_back();

    assert_test(mstack.size() == lstack.size(), "size matches std::list");

    mstack.push(3); mstack.push(5); mstack.push(737); mstack.push(0);
    lstack.push_back(3); lstack.push_back(5); lstack.push_back(737); lstack.push_back(0);

    // check iterators
    MutantStack<int>::iterator it = mstack.begin();
    MutantStack<int>::iterator ite = mstack.end();
    std::list<int>::iterator lit = lstack.begin();
    std::list<int>::iterator lite = lstack.end();

    // check increment/decrement
    ++it; --it;
    bool identical = true;
    while (it != ite && lit != lite) {
      if (*it != *lit) identical = false;
      ++it;
      ++lit;
    }
    assert_test(identical, "iterator content matches std::list");

    // check stack conversion
    std::stack<int> s(mstack);
    assert_test(s.size() == mstack.size(), "convertible to std::stack");
  }

  {
    MutantStack<char> ms;
    ms.push('a'); ms.push('b'); ms.push('c');

    // test reverse iterator
    MutantStack<char>::reverse_iterator rit = ms.rbegin();
    assert_test(*rit == 'c', "rbegin() is 'c'");
    assert_test(*(++rit) == 'b', "++rbegin() is 'b'");

    // test const iterator
    const MutantStack<char> cms = ms;
    MutantStack<char>::const_iterator cit = cms.begin();
    assert_test(*cit == 'a', "const_iterator begin() is 'a'");
    // *cit = 'z'; // uncommenting this should cause compile error
  }

  return 0;
}
