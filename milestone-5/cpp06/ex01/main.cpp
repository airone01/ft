#include "Serializer.hpp"
#include <iostream>

int main(void) {
  // Serializer this_will_not_compile;

  Data d;
  d.foo = "hi";
  d.bar = 42;
  d.baz = 42.0;

  Data *d2 = Serializer::deserialize(Serializer::serialize(&d));

  std::cout << "og ptr:  " << (&d) << std::endl;
  std::cout << "new ptr: " << d2 << std::endl;
  std::cout << ((d2 == &d) ? "OK" : "KO!") << std::endl;

  return 0;
}
