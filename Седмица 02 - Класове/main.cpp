#include <iostream>
#include "rational.hpp"
#include "test.hpp"

int main() {
  Rational rational(1, 2);

  std::cout << rational.get_numerator() << ' ' << rational.get_denominator() << '\n';
  return 0;
}