#ifndef RATIONAL_HPP
#define RATIONAL_HPP

class Rational {
public:
  Rational(int numerator, int denominator);

  int get_numerator() const;
  int get_denominator() const;

  void set_numerator(int);
  void set_denominator(int);

  void simplify();

private:
  int numerator;
  int denominator;

  int gcd() const;
};

#endif