#include "rational.hpp"
#include <algorithm>

Rational::Rational(int numerator, int denominator)
  : numerator(numerator), denominator(1) {
  set_denominator(denominator);
}

int Rational::get_numerator() const {
  return numerator;
}

int Rational::get_denominator() const {
  return denominator;
}

void Rational::set_numerator(int n) {
  numerator = n;
}

void Rational::set_denominator(int n) {
  if (n != 0) {
    denominator = n;
  }
}

void Rational::simplify() {
  int d = gcd();
  numerator /= d;
  denominator /= d;
}

int Rational::gcd() const {
  int max_number = std::max(numerator, denominator);
  int min_number = std::min(numerator, denominator);

  while (min_number != 0) {
    int temp = min_number;
    min_number = max_number % min_number;
    max_number = temp;
  }

  return max_number;
}